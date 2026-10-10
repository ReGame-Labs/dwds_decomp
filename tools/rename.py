#!/usr/bin/env python3
"""Renames symbols in the symbol files, the source and the headers.

    python tools/rename.py OLD NEW [OLD NEW ...]
    python tools/rename.py --table renames.txt

A table has one rename per line, `old new`, and `#` starts a comment. Each old
name is replaced as a whole word in src/, include/ and the symbols.txt files
of config/ (where it is the first word of a line). A name already renamed is
skipped, so a table can be run again after a rebase. It refuses a new name
that a symbol file already has for another symbol.
"""

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def read_pairs(args: argparse.Namespace) -> list[tuple[str, str]]:
    words = list(args.names)
    if args.table:
        for line in args.table.read_text().splitlines():
            words += line.split("#", 1)[0].split()
    if len(words) % 2:
        sys.exit("the names don't come in pairs")
    return list(zip(words[0::2], words[1::2]))


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("names", nargs="*", help="OLD NEW pairs")
    parser.add_argument("--table", type=Path, help="a file of OLD NEW lines")
    args = parser.parse_args()
    pairs = [(old, new) for old, new in read_pairs(args) if old != new]

    symbol_files = sorted(ROOT.glob("config/**/symbols.txt"))
    defined = {}
    for path in symbol_files:
        for line in path.read_text().splitlines():
            if line.strip():
                defined.setdefault(line.split()[0], path)
    for old, new in pairs:
        if new in defined and old in defined:
            sys.exit(f"{new} already names another symbol in {defined[new].relative_to(ROOT)}")

    paths = [*ROOT.glob("src/**/*.[ch]"), *ROOT.glob("include/**/*.h"), *symbol_files]
    changed = 0
    for path in paths:
        text = original = path.read_text()
        for old, new in pairs:
            if path.name == "symbols.txt":
                text = re.sub(rf"^{re.escape(old)}(?= )", new, text, flags=re.M)
            else:
                text = re.sub(rf"\b{re.escape(old)}\b", new, text)
        if text != original:
            path.write_text(text)
            changed += 1
    print(f"{len(pairs)} names, {changed} files changed")


if __name__ == "__main__":
    main()
