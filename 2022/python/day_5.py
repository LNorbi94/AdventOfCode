from collections import deque
import re

def put_in_crate(line, crates):
    crates_on_this_line = [line[i + 1:i + 2] for i in range(0, len(line), 4)]
    if not crates:
        for i in range(0, len(crates_on_this_line)):
            crates.append(deque())
    crate_idx = 0
    for crate in crates_on_this_line:
        stripped_crate = crate.strip()
        if stripped_crate:
            crates[crate_idx].appendleft(stripped_crate)
        crate_idx += 1


def move_crate(line, crates):
    match = re.findall(r'[0-9]+', line)
    if not match:
        return
    #print(match)
    count = int(match[0].strip())
    from_crate = int(match[1].strip()) - 1
    to_crate = int(match[2].strip()) - 1

    #print(f"Move {count} from {from_crate + 1} to {to_crate + 1}")
    #print(crates[from_crate])
    last_idx = len(crates[to_crate])
    for i in range(0, count):
        crates[to_crate].insert(last_idx, crates[from_crate].pop())

with open('src/day_5.txt') as f:
    crates = []
    crates_packed = False
    for line in f.readlines():
        crates_packed = crates_packed or '1' in line
        if not crates_packed:
            put_in_crate(line, crates)
        elif 'move' in line:
            move_crate(line, crates)
    print(crates)

    label = ""
    for crate in crates:
        label += crate.pop()
    print(label)