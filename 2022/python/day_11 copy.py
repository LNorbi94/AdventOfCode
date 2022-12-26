from collections import deque
from typing import Callable

class Monkey:
    def __init__(self, items : deque, worry_modifier : Callable[[int], int], throw_item : Callable[[int], None]) -> None:
        self.items = items
        self.worry_modifier = worry_modifier
        self.throw_item = throw_item
        self.inspected_items = 0
    
    def inspect_next_item(self):
        if len(self.items) == 0:
            return False
        self.inspected_items += 1
        next_item = self.items.popleft()
        print(f'Currently inspected item worry level is: {next_item}')
        next_item = self.worry_modifier(next_item)
        print(f'Currently inspected item worry level was modified to: {next_item}')
        next_item = int(next_item / 3)
        self.throw_item(next_item)
        return True

def convert_line_to_items(line):
    return [int(item) for item in line.split(':')[1].strip().split(', ')]

def create_addition(operands):
    left_side_old = 'old' in operands[0]
    right_side_old = 'old' in operands[1]
    if left_side_old and right_side_old:
        return lambda old : old + old
    if left_side_old:
        return lambda old : old + int(operands[1])
    if right_side_old:
        return lambda old : old + int(operands[0])

def create_multiplication(operands):
    left_side_old = 'old' in operands[0]
    right_side_old = 'old' in operands[1]
    if left_side_old and right_side_old:
        return lambda old : old * old
    if left_side_old:
        return lambda old : old * int(operands[1])
    if right_side_old:
        return lambda old : old * int(operands[0])

def get_worry_modifier(line):
    worry_modifier = line.split('=')[1].strip()
    add_operation = '+' in worry_modifier
    if add_operation:
        split_operation = worry_modifier.split('+')
        return create_addition(split_operation)
    else:
        split_operation = worry_modifier.split('*')
        return create_multiplication(split_operation)

def get_throw_item_logic(lines, i, monkeys):
    division = int(lines[i + 3].split('by')[1].strip())
    first_case = int(lines[i + 4].split('monkey')[1].strip())
    second_case = int(lines[i + 5].split('monkey')[1].strip())
    return lambda item : monkeys[first_case].items.append(item) if not item % division else monkeys[second_case].items.append(item)

with open('day_11.txt') as f:
    lines = f.readlines()
    monkeys = []
    for i in range(0, len(lines), 7):
        items = convert_line_to_items(lines[i + 1])
        monkeys.append(
            Monkey(
                deque(items),
                get_worry_modifier(lines[i + 2]),
                get_throw_item_logic(lines, i, monkeys)
            )
        )
    
    for i in range(0, 20):
        for j in range(0, len(monkeys)):
            #print(f'Currently Monkey{j} is inspecting items.')
            while monkeys[j].inspect_next_item():
                print('Inspecting next item...')
    
    for monkey in monkeys:
        print(f'Monkey inspected {monkey.inspected_items} after 20 rounds.')