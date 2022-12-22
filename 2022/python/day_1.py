
with open('src/day_1.txt') as f:
    calorie_sum = 0
    elfs = []
    for line in f.readlines():
        if line == '\n':
            elfs.append(calorie_sum)
            calorie_sum = 0
        else:
            calorie_sum += int(line)

    elfs.sort()

    #top_3_sum = [x + x for x in elfs[-3:]]
    #top_3_sum = map(lambda x: x + x, elfs[-3:])
    print(elfs[-3:])
    top_3_sum = sum(elfs[-3:])

    print(top_3_sum)