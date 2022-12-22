
class RockPath:
    def __init__(self, start, end) -> None:
        if start > end:
            self.start = end
            self.end = start
        else:
            self.start = start
            self.end = end

    def has_rock_here(self, x, y):
        if x < self.start[0] or x > self.end[0]:
            return False
        if y < self.start[1] or y > self.end[1]:
            return False
        return True

def can_reach_position(x, y, rock_paths, resting_sands):
    for resting_sand in resting_sands:
        if resting_sand[0] == x and resting_sand[1] == y:
            return False

    for rock_path in rock_paths:
        if rock_path.has_rock_here(x, y):
            return False

    return True

def move_sand(x, y, rock_paths, resting_sands):
    print(f'Sand is at {x} and {y}')
    new_x = x
    new_y = y + 1

    if can_reach_position(new_x, new_y, rock_paths, resting_sands):
        return (new_x, new_y)

    new_x = x - 1
    new_y = y + 1

    if can_reach_position(new_x, new_y, rock_paths, resting_sands):
        return (new_x, new_y)

    new_x = x + 1
    new_y = y + 1

    if can_reach_position(new_x, new_y, rock_paths, resting_sands):
        return (new_x, new_y)

    return (x, y)

def falling_to_the_void(y, rock_paths):
    highest_y = 0
    for rock_path in rock_paths:
        if rock_path.end[1] > highest_y:
            highest_y = rock_path.end[1]

    return y > highest_y


with open('src/day_14.txt') as f:
    rock_paths = []
    for line in f.readlines():
        line_points = line.split('->')
        print(line_points)
        for i in range(1, len(line_points)):
            start = [int(p) for p in line_points[i - 1].strip().split(',')]
            end = [int(p) for p in line_points[i].strip().split(',')]
            rock_paths.append(RockPath(start, end))

    for rock_path in rock_paths:
        print(f'Rock path start: {rock_path.start}, end: {rock_path.end}.')

    sand_position = (500, 0)
    resting_sands = []

    while not falling_to_the_void(sand_position[1], rock_paths):
        new_sand_position = move_sand(sand_position[0], sand_position[1], rock_paths, resting_sands)
        if new_sand_position == sand_position:
            resting_sands.append(sand_position)
            sand_position = (500, 0)
        else:
            sand_position = new_sand_position
    
    print(len(resting_sands))