import functools
import json

def compare_lists(left_list, right_list):
    print(f'Comparing {left_list} and {right_list}')
    for i in range(len(left_list)):
        if i + 1 > len(right_list):
            return (False, True)
        left_item = left_list[i]
        right_item = right_list[i]
        print(f'Inner Comparing {left_item} and {right_item}')
        if type(left_item) == int and type(right_item) == int:
            if left_item < right_item:
                return (True, True)
            if right_item < left_item:
                return (False, True)
        elif type(left_item) != int and type(right_item) == int:
            cmp_result = compare_lists(left_item, [ right_item ])
            if cmp_result[1]:
                return (cmp_result[0], True)
        elif type(left_item) == int and type(right_item) != int:
            print(f'{right_item} and i is {i}')
            cmp_result = compare_lists([ left_item ], right_item)
            if cmp_result[1]:
                return (cmp_result[0], True)
        elif type(left_item) != int and type(right_item) != int:
            cmp_result = compare_lists(left_item, right_item)
            if cmp_result[1]:
                return (cmp_result[0], True)
    if len(left_list) < len(right_list):
        return (True, True)
    return (False, False)

def compare_wrapper(left_list, right_list):
    if compare_lists(left_list, right_list)[0]:
        return -1
    else:
        return 1

def get_value(list):
    if type(list) == int:
        return 1 + list

    value = 0
    for item in list:
        value += get_value(item)

    return value

with open('/Users/lestarnorbert/rust/advent_of_code/src/day_13.txt') as f:
    input_lines = f.readlines()
    correct_pairs = []
    pair_index = 1
    lists = []
    #for i in range(0, len(input_lines), 3):
    #    left_code = (json.loads(input_lines[i]))
    #    right_code = (json.loads(input_lines[i + 1]))
    #    index_to_insert = 0
    #    for k in range(len(lists)):
    #        if compare_lists(lists[0], left_code)[0]:
    #            index_to_insert = k - 1
    #            break
    #    lists.insert(index_to_insert, left_code)
    #    index_to_insert = 0
    #    for k in range(len(lists)):
    #        if compare_lists(lists[0], right_code)[0]:
    #            index_to_insert = k - 1
    #            break
    #    lists.insert(index_to_insert, right_code)
#
    for i in range(len(input_lines)):
        if input_lines[i] != '\n':
            lists.append(json.loads(input_lines[i]))
    #print(sorted(lists, key=get_value))
    sorted_list = (sorted(lists, key=functools.cmp_to_key(compare_wrapper)))
    two_idx = 0
    six_idx = 0
    for item in sorted_list:
        two_idx += 1
        if type(item) != int and len(item) == 1:
            if type(item[0]) != int and len(item[0]) == 1:
                if item[0][0] == 2:
                    break
    for item in sorted_list:
        six_idx += 1
        if type(item) != int and len(item) == 1:
            if type(item[0]) != int and len(item[0]) == 1:
                if item[0][0] == 6:
                    break

    print(two_idx * six_idx)