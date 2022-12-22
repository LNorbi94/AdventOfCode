
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

    def add_rocks(self, blocking_items):
        if self.start[0] != self.end[0]:
            y = self.start[1]
            #print('h')
            for x in range(self.start[0], self.end[0] + 1):
                #print(f'{x} and {y}')
                blocking_items[coords_to_text((x, y))] = '.'
        if self.start[1] != self.end[1]:
            x = self.start[0]
            for y in range(self.start[1], self.end[1] + 1):
                #print(f'{x} and {y}')
                blocking_items[coords_to_text((x, y))] = '.'

def can_reach_position(x, y, rock_paths, resting_sands, highest_y):
    for resting_sand in resting_sands:
        if resting_sand[0] == x and resting_sand[1] == y:
            return False

    highest_y = 0
    for rock_path in rock_paths:
        if rock_path.has_rock_here(x, y):
            return False

    return y >= highest_y + 2

def move_sand(x, y, blocking_items, highest_y):
    #print(f'Sand is at {x} and {y}')

    possible_moves = []

    new_x = x
    new_y = y + 1
    possible_moves.append((new_x, new_y))

    new_x = x - 1
    new_y = y + 1
    possible_moves.append((new_x, new_y))

    new_x = x + 1
    new_y = y + 1
    possible_moves.append((new_x, new_y))

    for possible_move in possible_moves:
        if not coords_to_text(possible_move) in blocking_items:
                if possible_move[1] < highest_y + 2:
                    return possible_move

    return (x, y)

def falling_to_the_void(y, rock_paths):
    highest_y = 0
    for rock_path in rock_paths:
        if rock_path.end[1] > highest_y:
            highest_y = rock_path.end[1]

    return y > highest_y


def coords_to_text(coords):
    return f'{coords}'

with open('src/day_14.txt') as f:
    rock_paths = []
    highest_y = 0
    blocking_items = dict()
    for line in f.readlines():
        line_points = line.split('->')
        for i in range(1, len(line_points)):
            start = [int(p) for p in line_points[i - 1].strip().split(',')]
            end = [int(p) for p in line_points[i].strip().split(',')]
            rock_paths.append(RockPath(start, end))
            if start[1] > highest_y:
                highest_y = start[1]
            if end[1] > highest_y:
                highest_y = end[1]

    sand_position = (500, 0)
    resting_sands = []

    for rock_path in rock_paths:
        rock_path.add_rocks(blocking_items)

    while not (500, 0) in resting_sands:
        new_sand_position = move_sand(sand_position[0], sand_position[1], blocking_items, highest_y)
        if new_sand_position == sand_position:
            resting_sands.append(sand_position)
            blocking_items[coords_to_text(sand_position)] = '.'
            sand_position = (500, 0)
        else:
            sand_position = new_sand_position
    
    print(len(resting_sands))