
with open('src/day_6.txt') as f:
    for line in f.readlines():
        for i in range(0, len(line) - 3):
            char_set = set([line[j] for j in range(i, i + 14)])
            if len(char_set) >= 14:
                print(i + 14)
                break
