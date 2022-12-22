
class Position:
    def __init__(self, x, y, name) -> None:
        self.x = x
        self.y = y
        self.name = name
        self.positions = set()

    def move(self, move_command):
        print(f'Moving {self.name} to {move_command}')
        if move_command == 'R':
            self.x += 1
        elif move_command == 'L':
            self.x -= 1
        elif move_command == 'U':
            self.y += 1
        elif move_command == 'D':
            self.y -= 1
        

    def follow(self, other_position):
        moves_needed = []
        print(f'Self: {self.x}, {self.y}. Other: {other_position.x}, {other_position.y}')
        if abs(self.x - other_position.x) > 1:
            if self.x < other_position.x:
                moves_needed.append('R')
            elif self.x > other_position.x:
                moves_needed.append('L')
            if abs(self.y - other_position.y) >= 1:
                if self.y < other_position.y:
                    moves_needed.append('U')
                elif self.y > other_position.y:
                    moves_needed.append('D')
        elif abs(self.y - other_position.y) > 1:
            if self.y < other_position.y:
                moves_needed.append('U')
            elif self.y > other_position.y:
                moves_needed.append('D')
            if abs(self.x - other_position.x) >= 1:
                if self.x < other_position.x:
                    moves_needed.append('R')
                elif self.x > other_position.x:
                    moves_needed.append('L')

        for move_needed in moves_needed:
            self.move(move_needed)

        self.positions.add((self.x, self.y))
    
    def touched_positions(self):
        for position in sorted(self.positions):
            print(f'X: {position[0]}, Y: {position[1]}')
        return len(self.positions)

with open('src/day_9.txt') as f:
    head = Position(0, 0, 'Head')
    tail = Position(0, 0, 'Tail')
    for line in f.readlines():
        split_line = line.split(' ')
        command = split_line[0].strip()
        repeat_count = int(split_line[1].strip())
        for i in range(0, repeat_count):
            head.move(command)
            tail.follow(head)
    
    print(tail.touched_positions())