#!/usr/bin/env python3
"""Count the workarounds the matched C needs, by the markers they carry, and
fail on what the source must never have.

    tools/hacks.py          the counts; fails on forbidden code
    tools/hacks.py --list   every one, with its file and line

Every spot where the C only matches through a form natural C wouldn't take
carries a comment that says so. This finds them in src/ and include/:

- fake matches: a comment that starts with "fake match:", the last resort,
  a form forced only for the codegen;
- form-dependent matches: a comment that says "match depends on", where the
  match needs one of several equivalent forms.

A function either matches as C or stays out of src/ (delinked from the
original), so these always fail:

- NON_MATCHING (or NONMATCHING) code, and #if 0 blocks: C that doesn't
  match, or a draft, doesn't belong in src/;
- assembly in place of C: mwcc's asm functions and asm blocks, and the
  asm() of GCC syntax.
"""

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DIRS = ("src", "include")
SUFFIXES = (".c", ".cpp", ".h", ".hpp", ".inc")

COUNTED = {
    "fake matches": re.compile(r"/\*\s*fake match:", re.I),
    "form-dependent matches": re.compile(r"match depends on", re.I),
}
FORBIDDEN = {
    "lines of NON_MATCHING code": re.compile(r"\bNON_?MATCHING\b"),
    "#if 0 blocks": re.compile(r"^\s*#\s*if\s+0\b"),
    "lines of assembly": re.compile(r"\b(?:__asm__|__asm|asm)\b\s*(?:volatile\s*)?[({]|^\s*(?:\w+\s+)*asm\s+\w[\w\s\*]*\("),
}


def scan():
    found = {k: [] for k in (*COUNTED, *FORBIDDEN)}
    for d in DIRS:
        for path in sorted((ROOT / d).rglob("*")):
            if path.suffix not in SUFFIXES:
                continue
            for n, line in enumerate(path.read_text(errors="replace").splitlines(), 1):
                for kind, pattern in (*COUNTED.items(), *FORBIDDEN.items()):
                    if pattern.search(line):
                        found[kind].append(f"{path.relative_to(ROOT)}:{n}: {line.strip()}")
    return found


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--list", action="store_true", help="show every one")
    args = parser.parse_args()

    found = scan()
    for kind, hits in found.items():
        print(f"{len(hits):5} {kind}")
        if args.list or (kind in FORBIDDEN and hits):
            for hit in hits:
                print(f"        {hit}")
    if any(found[k] for k in FORBIDDEN):
        sys.exit("forbidden code in src/ or include/")


if __name__ == "__main__":
    main()
