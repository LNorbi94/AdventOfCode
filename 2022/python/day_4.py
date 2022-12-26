
def get_priority(char):
    print(char)
    if char == '\n':
        return 0
    if ord(char) >= ord('a') and ord(char) <= ord('z'):
        return ord(char) - 96
    return ord(char) - 38


with open('day_3.txt') as f:
    priority_sum = 0
    lines = f.readlines()
    for j in range(0, len(lines), 3):
        intersection = set()
        for k in range(j, j + 3):
            inner_intersection = set()
            for ch in lines[k]:
                inner_intersection.add(ch)
            
            #print(intersection)
            if k > j:
                intersection = intersection.intersection(inner_intersection)
            else:
                intersection = inner_intersection
            #print(intersection)
        
        for element in intersection:
            priority_sum += get_priority(element)
    
    print(priority_sum)