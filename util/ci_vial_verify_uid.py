#!/usr/bin/env python3
from glob import glob
from pathlib import Path
import re
import sys
import struct
from collections import defaultdict

def main():

    VIAL_UID_REGEX = re.compile(r"#\s*define\s+VIAL_KEYBOARD_UID\s+(?:\\(?:\n|\r)\s*)*{\s*((?:0(?:x|X)(?:[0-9a-fA-F]){2}\s*,\s*){7}(?:0(?:x|X)(?:[0-9a-fA-F]){2}))\s*}")

    error = 0
    uid_to_keyboards = defaultdict(set)

    for filename in glob("keyboards/**/vial.json", recursive=True):
        keyboard = filename[10:-10].split("/keymaps/")[0]

        dirname = Path(filename).parents[0]
        uid = None

        while True:
            config_h = dirname.joinpath("config.h")
            if config_h.exists() and config_h.stat().st_size < 100000:
                content = config_h.read_text()
                uid = VIAL_UID_REGEX.search(content)
            if uid:
                break
            dirname = dirname.parents[0]
            if dirname.match("keyboards"):
                break

        if not uid:
            print("Keyboard {} does not define a VIAL_KEYBOARD_UID".format(keyboard))
            error = 1
            continue

        uid = uid[1].split(",")
        uid.reverse()
        uid = [int(x, 16) for x in uid]
        uid = struct.pack("BBBBBBBB", *uid).hex()
        uid_to_keyboards[uid].add(keyboard)

        print("{} uses UID {}".format(keyboard, uid))

    for uid, keyboards in uid_to_keyboards.items():
        if len(keyboards) > 1:
            print("UID {} duplicated: {}".format(uid, keyboards))
            error = 1

    return error

if __name__ == "__main__":
    sys.exit(main())
