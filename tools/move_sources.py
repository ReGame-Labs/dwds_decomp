#!/usr/bin/env python3
"""Moves source files and their headers, and updates everything that names them.

Reads a table of moves, one per line, `old new` (paths of .c files under src/,
or of headers under include/ that have no .c file, `#` starts a comment), and
for each:
- moves src/<old>.c to src/<new>.c and include/<old>.h to include/<new>.h with
  git mv, when the header exists;
- rewrites the file's entry in the delinks.txt files of config/;
- rewrites `#include "<old>.h"` everywhere in src/ and include/, and the
  header's guard.

Moves already made are skipped, so the table can be run again after a rebase.
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def guard(path: str) -> str:
    return re.sub(r"[^A-Za-z0-9]", "_", path).upper()


def read_moves(table: Path) -> list[tuple[str, str, str]]:
    moves = []
    for line in table.read_text().splitlines():
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        old, new = line.split()
        kind = "h" if old.endswith(".h") else "c"
        strip = lambda path: path.removeprefix("src/").removeprefix("include/").removesuffix(".c").removesuffix(".h")
        moves.append((kind, strip(old), strip(new)))
    return moves


def git_mv(old: Path, new: Path) -> None:
    new.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(["git", "mv", str(old), str(new)], cwd=ROOT, check=True)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("table", type=Path, help="the table of moves")
    args = parser.parse_args()

    moves = [move for move in read_moves(args.table) if move[1] != move[2]]
    texts = {}
    for path in [*ROOT.glob("src/**/*.[ch]"), *ROOT.glob("include/**/*.h"), *ROOT.glob("config/**/delinks.txt")]:
        texts[path] = path.read_text()

    done = 0
    for kind, old, new in moves:
        old_c, new_c = ROOT / "src" / f"{old}.c", ROOT / "src" / f"{new}.c"
        old_h, new_h = ROOT / "include" / f"{old}.h", ROOT / "include" / f"{new}.h"
        moved = old_c.exists() if kind == "c" else old_h.exists()
        if kind == "c" and old_c.exists():
            git_mv(old_c, new_c)
            texts[new_c] = texts.pop(old_c)
        elif kind == "c" and not new_c.exists():
            sys.exit(f"neither src/{old}.c nor src/{new}.c exists")
        if old_h.exists():
            git_mv(old_h, new_h)
            texts[new_h] = texts.pop(old_h)
        elif kind == "h" and not new_h.exists():
            sys.exit(f"neither include/{old}.h nor include/{new}.h exists")
        done += moved
        if new_h in texts:
            texts[new_h] = re.sub(rf"\b{guard(old)}_H\b", f"{guard(new)}_H", texts[new_h])

        include = re.compile(rf'#include "{re.escape(old)}\.h"')
        entry = re.compile(rf"^src/{re.escape(old)}\.c:", re.M)
        for path, text in texts.items():
            text = include.sub(f'#include "{new}.h"', text)
            if path.name == "delinks.txt":
                text = entry.sub(f"src/{new}.c:", text)
            texts[path] = text

    for path, text in texts.items():
        if path.exists() and path.read_text() != text:
            path.write_text(text)

    for directory in sorted({*ROOT.glob("src/**/"), *ROOT.glob("include/**/")}, reverse=True):
        if directory.is_dir() and not any(directory.iterdir()):
            directory.rmdir()
    print(f"{done} of {len(moves)} files moved")


if __name__ == "__main__":
    main()
