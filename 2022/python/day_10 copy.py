
with open('day_10.txt') as f:
    x = 1
    cycle = 1
    sum = 0
    for line in f.readlines():
        if cycle in [20, 60, 100, 140, 180, 220]:
            sum += (x * cycle)
            print((x * cycle))
        if 'noop' in line:
            cycle += 1
            continue
        to_add = int(line.split(' ')[1])
        if cycle + 1 in [20, 60, 100, 140, 180, 220]:
            sum += (x * (cycle + 1))
            print(x * (cycle + 1))
        x += to_add
        cycle += 2
    print(sum)