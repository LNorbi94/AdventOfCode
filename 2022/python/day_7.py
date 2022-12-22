import re
from collections import deque

class Directory:

    def __init__(self, name, parent = None) -> None:
        self.directories = {}
        self.size = 0
        self.name = name
        self.parent = parent
        self.level = 0 if parent is None else self.parent.level + 1

    def add_directory(self, directory):
        self.directories[directory.name] = directory

    def get_directory(self, name):
        return self.directories.get(name)

    def has_directory(self, name):
        return name in self.directories.keys()

    def add_size(self, size):
        self.size += size

    def calculate_size(self):
        size = self.size
        for directory in self.directories:
            size += self.directories[directory].calculate_size()
        
        return size
    
    def print(self):
        print('--' * self.level + ' ' + self.name + f' , size: {self.calculate_size()}')

with open('src/day_7.txt') as f:
    actual_dir = Directory('/')
    for line in f.readlines():
        if line[0] == '$':
            if "cd" in line:
                to_directory = line[5:].strip()
                if actual_dir.name == '/' and actual_dir.name == to_directory:
                    continue
                elif ".." in to_directory:
                    #print(f'Was at: {actual_dir.name}')
                    if not actual_dir.parent is None:
                        actual_dir = actual_dir.parent
                    #print(f'Go up a level: {actual_dir.name}')
                else:
                    if not actual_dir.has_directory(to_directory):
                        print(f'Creating dir from change dir: {to_directory}, parent will be: {actual_dir.name}')
                        actual_dir.add_directory(Directory(to_directory, actual_dir))

                    actual_dir = actual_dir.get_directory(to_directory)
                    #print(f'Change to {to_directory}')
        else:
            split_line = line.split(' ')
            if not split_line[0] == 'dir':
                actual_dir.add_size(int(split_line[0]))
            elif not actual_dir is None:
                to_directory = split_line[1].strip()
                if not actual_dir.has_directory(to_directory):
                    print(f'Creating dir: {to_directory}, parent will be: {actual_dir.name}')
                    actual_dir.add_directory(Directory(to_directory, actual_dir))
    
    #print(f'Name: {actual_dir.name}, size: {actual_dir.calculate_size()}, parent: {actual_dir.parent.name}')
    while not actual_dir.parent is None:
        actual_dir = actual_dir.parent
    #print(f'Name: {actual_dir.name}, size: {actual_dir.calculate_size()}')

    #actual_dir.print()
    sum_of_dirs = 0
    directories = deque()
    directories.append(actual_dir)
    smallest_dir = 70000000
    # 30000000 kell összesen
    # 70000000 van összesen
    current_free_space = 70000000 - actual_dir.calculate_size()
    while directories:
        actual_dir = directories.pop()
        actual_dir.print()
        actual_size = actual_dir.calculate_size()
        print(current_free_space)
        if actual_size + current_free_space >= 30000000 and actual_size < smallest_dir:
            smallest_dir = actual_size

        for directory in actual_dir.directories:
            directories.append(actual_dir.directories.get(directory))

    print(smallest_dir)