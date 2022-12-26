
with open('day_3.txt') as f:
    partial_covers = 0
    for line in f.readlines():
        sectors = line.split(',')
        first_sector = sectors[0].split('-')
        second_sector = sectors[1].split('-')

        first_sector_set = set(range(int(first_sector[0]), int(first_sector[1]) + 1))
        second_sector_set = set(range(int(second_sector[0]), int(second_sector[1]) + 1))

        print(first_sector_set)
        print(second_sector_set)

        if first_sector_set.intersection(second_sector_set):
            partial_covers += 1
    
    print(partial_covers)