#!/usr/bin/env python3
"""Compile a draft with the project's compiler and compare its functions with
the original.

    tools/try_match.py draft.c                 every func_* the draft defines
    tools/try_match.py draft.c func_0203e8d8   only these
    tools/try_match.py -v usa draft.c          another version (default: usa)

A function named func_XXXXXXXX is compared with the ARM9 program or the ITCM,
and func_ovNNN_XXXXXXXX with overlay NNN; give other names as name=address
(func=0x0203e8d8, or func=ov002:0x0224740c). Prints MATCH, or both versions
side by side with the differing instructions marked **. Relocated fields
(call targets, literal pool words) are masked, so only the code counts.

Run `python tools/configure.py <version>` and `ninja` first: the compiler
command comes from build.ninja and the original from extract/<version>/.
"""

import argparse
import re
import shlex
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

ROOT = Path(__file__).resolve().parent.parent


def compiler_command(version):
    text = (ROOT / "build.ninja").read_text().replace("$\n", "")
    rule = re.search(r"^rule mwcc\n\s+command = (.*)$", text, re.M)
    if rule is None:
        sys.exit("build.ninja has no mwcc rule; run tools/configure.py first")
    command = rule.group(1).split(" $cc_flags")[0]
    return shlex.split(command) + ["-d", version]


def overlay_bases(version):
    text = (ROOT / f"extract/{version}/arm9_overlays/overlays.yaml").read_text()
    ids = [int(x) for x in re.findall(r"- id: (\d+)", text)]
    bases = [int(x) for x in re.findall(r"base_address: (\d+)", text)]
    return dict(zip(ids, bases))


def original(version, name, address):
    """The module's bytes, its base address and the function's address."""
    extract = ROOT / f"extract/{version}"
    if address is None:
        m = re.fullmatch(r"func_(?:ov(\d{3})_)?([0-9a-f]{8})", name)
        if m is None:
            sys.exit(f"{name}: give its address as {name}=0x...")
        overlay, address = m.group(1), m.group(2)
        address = f"ov{overlay}:0x{address}" if overlay else f"0x{address}"
    if ":" in address:
        overlay, address = address.split(":")
        k = int(overlay[2:])
        return (extract / f"arm9_overlays/ov{k:03}.bin").read_bytes(), overlay_bases(version)[k], int(address, 16)
    address = int(address, 16)
    if address < 0x02000000:
        return (extract / "arm9/itcm.bin").read_bytes(), 0x01FF8000, address
    return (extract / "arm9/arm9.bin").read_bytes(), 0x02000000, address


def read_elf(path):
    """The functions of an object: name -> (code, relocated offsets, thumb)."""
    b = path.read_bytes()
    shoff, = struct.unpack_from("<I", b, 0x20)
    shentsize, shnum = struct.unpack_from("<HH", b, 0x2E)
    sections = [struct.unpack_from("<10I", b, shoff + i * shentsize) for i in range(shnum)]
    symtab = next(s for s in sections if s[1] == 2)
    strtab = sections[symtab[6]]

    def string(offset):
        start = strtab[4] + offset
        return b[start:b.index(b"\0", start)].decode()

    relocs = {}
    for s in sections:
        if s[1] in (4, 9):  # SHT_RELA, SHT_REL
            size = 12 if s[1] == 4 else 8
            offsets = relocs.setdefault(s[7], set())
            offsets.update(struct.unpack_from("<I", b, s[4] + i * size)[0] for i in range(s[5] // size))
    functions = {}
    for i in range(symtab[5] // 16):
        name, value, size, info, _, shndx = struct.unpack_from("<IIIBBH", b, symtab[4] + i * 16)
        if info & 0xF != 2:  # STT_FUNC
            continue
        thumb = value & 1
        value &= ~1
        section = sections[shndx]
        code = b[section[4] + value:section[4] + value + size]
        offsets = {r - value for r in relocs.get(shndx, ()) if value <= r < value + size}
        functions[string(name)] = (code, offsets, thumb)
    return functions


def masked(word, relocated, thumb):
    if not relocated:
        return word
    if not thumb and (word >> 25) & 7 == 5:  # b, bl, blx: keep the condition and opcode
        return word & 0xFF000000
    if thumb and (word & 0xF800) == 0xF000:  # bl/blx pair
        return word & 0xF800F800
    return None  # a literal pool word: anything goes


def disassemble(md, code, address):
    out = []
    step = 2 if md.mode == CS_MODE_THUMB else 4
    offset = 0
    while offset < len(code):
        ins = next(md.disasm(code[offset:offset + 4], address + offset, 1), None)
        if ins is None:
            out.append((offset, f".word {struct.unpack_from('<I', code.ljust(offset + 4, b'\0'), offset)[0]:#010x}"))
            offset += 4
            continue
        out.append((offset, f"{ins.mnemonic} {ins.op_str}".strip()))
        offset += ins.size if step == 2 else 4
    return out


def compare(name, code, offsets, thumb, rom, base, address):
    ref = rom[address - base:address - base + len(code)]
    differ = set()
    for o in range(0, len(code), 4):
        ours, theirs = (struct.unpack_from("<I", x.ljust(o + 4, b"\0"), o)[0] for x in (code, ref))
        relocated = o in offsets or (thumb and o + 2 in offsets)
        a, b = masked(ours, relocated, thumb), masked(theirs, relocated, thumb)
        if a is not None and a != b:
            differ.add(o)
    if not differ and len(ref) == len(code):
        print(f"{name}: MATCH")
        return True
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
    ours, theirs = disassemble(md, code, address), disassemble(md, ref, address)
    print(f"{name}: {len(differ)} differing words")
    for k in range(max(len(ours), len(theirs))):
        o, a = ours[k] if k < len(ours) else (None, "")
        _, b = theirs[k] if k < len(theirs) else (None, "")
        mark = "**" if o is None or (o & ~3) in differ else "  "
        print(f"{mark} {a:40} {b}")
    return False


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("-v", "--version", default="usa")
    parser.add_argument("draft", type=Path)
    parser.add_argument("functions", nargs="*")
    args = parser.parse_args()

    wanted = {}
    for f in args.functions:
        name, _, address = f.partition("=")
        wanted[name] = address or None
    lang = "-lang=c++" if args.draft.suffix == ".cpp" else "-lang=c"
    with tempfile.TemporaryDirectory() as tmp:
        obj = Path(tmp) / "draft.o"
        command = compiler_command(args.version) + [lang, "-c", str(args.draft), "-o", str(obj)]
        result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True)
        if result.returncode != 0:
            sys.exit(result.stdout + result.stderr)
        functions = read_elf(obj)
    if not wanted:
        wanted = {n: None for n in functions if n.startswith("func_")}
    ok = True
    for name, address in wanted.items():
        if name not in functions:
            print(f"{name}: not in the draft")
            ok = False
            continue
        rom, base, at = original(args.version, name, address)
        ok &= compare(name, *functions[name], rom, base, at)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
