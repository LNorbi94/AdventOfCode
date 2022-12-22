import json

def compare_codes_v1(left_code, right_code):
    left_code = left_code.strip()
    right_code = right_code.strip()
    print(f'Comparing {left_code} and {right_code}')
    #try:
    left_list_depth = 0
    right_list_depth = 0
    for i in range(len(left_code)):
        left_idx = i - (right_list_depth - left_list_depth if right_list_depth > left_list_depth else 0)
        right_idx = i - (left_list_depth - right_list_depth if left_list_depth > right_list_depth else 0)
        print(f'Currently at: {left_idx} and {right_idx} and i is {i}')
        if len(right_code) < right_idx + 1:
            print(f'Right code was shorter: {right_code}. Tried to get: {right_idx}, left index was: {left_idx} and i was: {i}')
            return False
        if len(left_code) < left_idx + 1:
            print(f'Left code was shorter: {left_code}')
            return True
        start_of_list = False
        if left_code[left_idx] == '[':
            start_of_list = True
            left_list_depth += 1
        #print(f'Right code length: {len(right_code)}, and idx: {right_idx}')
        if right_code[right_idx] == '[':
            start_of_list = True
            right_list_depth += 1
        if left_code[left_idx] == ']':
            left_list_depth -= 1
        #print(f'Right code length: {len(right_code)}, and idx: {right_idx}')
        if right_code[right_idx] == ']':
            right_list_depth -= 1
        if left_list_depth != right_list_depth and start_of_list:
            print(f'Skipping {i}')
            continue
        if left_code[left_idx].isnumeric() and right_code[right_idx].isnumeric():
            left_number = int(left_code[left_idx])
            right_number = int(right_code[right_idx])
            print(f'Comparing {left_number} and {right_number}')
            if left_number < right_number:
                return True
            elif left_number > right_number:
                return False
    return len(left_code) < len(right_code)
    #except:
    #    print(f'Exception happened')
    #    return False

def slice_list(list_to_slice):
    list_copy = (list_to_slice.strip()[1:])[:-1]

    if list_to_slice.count('[') <= 1:
        return list_copy.strip('[').strip(']').split(',')

    groups = []
    actual_group = ""

    brace_count = 0
    for item in list_copy:
        if item == ',' and not actual_group:
            continue
        elif item == '[':
            if brace_count == 0 and actual_group:
                groups.append(actual_group[:-1])
                actual_group = "["
                brace_count += 1
                continue
            brace_count += 1
        elif item == ']':
            brace_count -= 1
            if brace_count == 0:
                actual_group += item
                groups.append(actual_group)
                actual_group = ""
                continue

        actual_group += item

    if actual_group:
        groups.append(actual_group)
    return groups

def compare_codes(left_code, right_code):
    left_sliced = slice_list(left_code)
    print(left_sliced)
    right_sliced = slice_list(right_code)
    
    return compare_sliced_codes(left_sliced, right_sliced)

def compare_sliced_codes(left_sliced, right_sliced):
    print(f'Outside Comparing {left_sliced} and {right_sliced}')
    result = False
    for i in range(len(left_sliced)):
        left_item = left_sliced[i]
        if len(right_sliced) < i + 1:
            result = result or False
            break
        right_item = right_sliced[i]

        print(f'Comparing {left_item} and {right_item}')

        left_is_single_list = left_item.count('[') < 1
        right_is_single_list = right_item.count('[') < 1

        if left_is_single_list and right_is_single_list:
            left_bared_item = left_item.split(',')
            right_bared_item = (right_item.split(','))

            for j in range(len(left_bared_item)):
                if len(right_bared_item) < j + 1:
                    return False
                if len(left_bared_item[j]) == 0:
                    return True
                if len(right_bared_item[j]) == 0:
                    return True
                left_number = int(left_bared_item[j])
                right_number = int(right_bared_item[j])

                if left_number < right_number:
                    return True
                if right_number < left_number:
                    return False
            if i + 1 == len(left_sliced) and len(left_bared_item) < len(right_bared_item):
                return True
        elif left_is_single_list and not right_is_single_list:
            result = result or compare_sliced_codes(left_item, slice_list(right_item))
        elif not left_is_single_list and right_is_single_list:
            result = result or compare_sliced_codes(slice_list(left_item), (right_item))
        elif not left_is_single_list and not right_is_single_list:
            result = result or compare_sliced_codes(slice_list(left_item), slice_list(right_item))
    return result

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

def compare_lists_cv(left_list, right_list):
    for i in range(len(left_list)):
        converted_left = left_list[i]
        converted_right = right_list[i]
        if type(converted_left) == int:
            converted_left = [ converted_left ]
        if type(converted_right) == int:
            converted_right = [ converted_right ]
        if converted_left < converted_right:
            return True
        if converted_left > converted_right:
            return False

with open('/Users/lestarnorbert/rust/advent_of_code/src/day_13.txt') as f:
    input_lines = f.readlines()
    correct_pairs = []
    pair_index = 1
    for i in range(0, len(input_lines), 3):
        #print(slice_list(input_lines[i]))
        left_code = (json.loads(input_lines[i]))
        right_code = (json.loads(input_lines[i + 1]))
        if compare_lists(left_code, right_code)[0]:
        #if compare_codes_v1(input_lines[i], input_lines[i + 1]):
            print('ok')
            correct_pairs.append(pair_index)
        pair_index += 1

    sum_of_correct_pairs = 0
    for correct_pair in correct_pairs:
        sum_of_correct_pairs += correct_pair

    print(correct_pairs)
    print(sum_of_correct_pairs)