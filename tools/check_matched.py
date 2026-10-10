#!/usr/bin/env python3
"""Fail unless every function written in C matches the original exactly.

    tools/check_matched.py [version]   (default: usa; run `ninja report` first)

`ninja check` only sees the files marked `complete` in delinks.txt, which are
linked in place of the original. The others are compiled for objdiff alone, so
this reads objdiff's report and fails on any function of theirs that is C but
not a 100% match.
"""

import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def main():
    version = sys.argv[1] if len(sys.argv) > 1 else "usa"
    report = json.loads((ROOT / f"build/{version}/report.json").read_text())
    bad = []
    matched = 0
    for unit in report["units"]:
        for function in unit.get("functions", []):
            percent = function.get("fuzzy_match_percent")
            if percent is None:
                continue  # still delinked from the original
            if percent < 100.0:
                bad.append(f"{unit['name']}: {function['name']} {percent:.2f}%")
            else:
                matched += 1
    print(f"{matched} functions in C match")
    for line in bad:
        print(f"not matching: {line}")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
