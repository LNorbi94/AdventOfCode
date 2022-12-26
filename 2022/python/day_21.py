import queue

class Number:
    def __init__(self, label, left, right, operation, number) -> None:
        self.operation = None
        if '-' == operation:
            self.operation = lambda x, y : x - y
        if '+' == operation:
            self.operation = lambda x, y : x + y
        if '/' == operation:
            self.operation = lambda x, y : x / y
        if '*' == operation:
            self.operation = lambda x, y : x * y
        
        self.operator = operation

        self.number = float(number)
        self.calculated = left is None and right is None
        self.label = label
        self.left = left
        self.right = right

        self.left_dependencies = []
        self.right_dependencies = []

    def can_be_calculated(self):
        return not self.left is None and numbers[self.left].calculated and numbers[self.right].calculated and not 'humn' in self.left_dependencies and not 'humn' in self.right_dependencies

    def determine_dependencies(self):
        self.determine_side_dependencies(self.left_dependencies, self.left)
        self.determine_side_dependencies(self.right_dependencies, self.right)

    def should_make_it_equal_to(self, number):
        calculated_number = 0
        left = numbers[self.left] if self.left in numbers else None
        right = numbers[self.right] if self.right in numbers else None
        #print(left)
        #print(right)
        if self.calculated:
            return None
        if self.label == 'humn':
            self.number = number
            self.calculated = True
            return number
        self.determine_dependencies()
        if not 'humn' in self.left_dependencies and not 'humn' in self.right_dependencies:
            for dep in reversed(self.left_dependencies):
                numbers[dep].calculate()
            if left:
                left.calculate()
            for dep in reversed(self.right_dependencies):
                numbers[dep].calculate()
            if right:
                right.calculate()
            self.calculate()
            return None
        if left and right and left.calculated:
            print(f'{self.label} Left is calculated: {left.number}')
            print(f'{self.label} Number: {number}')
            # 100 == 50 - x
            # 100 (num) == 50 (l.n) / right.number
            # num / right.number = l.n
            # right.number = l.n * n
            if '-' == self.operator:
                right.number = left.number - number
            if '+' == self.operator:
                right.number = number - left.number
            if '/' == self.operator:
                right.number = number * left.number
            if '*' == self.operator:
                right.number = number / left.number
            
            print(right.number)
            calculated_number = right.number
        elif left and right and right.calculated:
            print(f'Right is calculated: {right.number}')
            # 100 == left.number * 50
            # num / r.n = l.n
            # 100 == left.number / 50
            # num * rn
            # 100 == 50 + l.n
            # 100 + ln == 50
            # ln = r.n - n
            if '-' == self.operator:
                left.number = right.number + number
            if '+' == self.operator:
                left.number = number - right.number
            if '/' == self.operator:
                left.number = right.number * number
            if '*' == self.operator:
                left.number = number / right.number

            calculated_number = left.number
        else:
            #self.determine_dependencies()
            if not 'humn' in self.left_dependencies:
                for dep in reversed(self.left_dependencies):
                    numbers[dep].calculate()
                left.calculate()
            elif not 'humn' in self.right_dependencies:
                for dep in reversed(self.right_dependencies):
                    numbers[dep].calculate()
                right.calculate()
            return self.should_make_it_equal_to(number)

        #self.number = calculated_number
        return calculated_number

    def determine_side_dependencies(self, determined_dependencies, number):
        if number is None:
            return

        dependencies = queue.Queue()
        dependencies.put(number)
        while not dependencies.empty():
            number = dependencies.get()
            if not number is None:
                determined_dependencies.append(number)
                dependencies.put(numbers[number].left)
                dependencies.put(numbers[number].right)

    def calculate(self):
        if self.calculated:
            return self.number
        if not self.operation:
            print(f'WTF {self.label}')
            return self.number
        self.number = self.operation(numbers[self.left].number, numbers[self.right].number)
        self.calculated = True

with open(r'day_21.txt') as f:
    lines = f.readlines()
    # root: pppw + sjmn
    numbers = dict()
    for line in lines:
        split_line = line.split(':')
        name = split_line[0].strip()
        num = 0
        if split_line[1].strip().isnumeric():
            num = int(split_line[1].strip())
            numbers[name] = Number(name, None, None, None, num)
        else:
            split_operation = split_line[1].strip().split(' ')
            numbers[name] = Number(name, split_operation[0], split_operation[2], split_operation[1], 0)

    #for n in numbers:
    #    number = numbers[n]
    #    number.determine_dependencies()

    #print(numbers['root'].number)
    numbers['root'].determine_dependencies()
    numbers['humn'].calculated = False
    numbers['humn'].number = 0

    #print(numbers['root'].right_dependencies)

    if 'humn' in numbers['root'].left_dependencies:
        for dependency in reversed(numbers['root'].right_dependencies):
            numbers[dependency].calculate()

        numbers['root'].calculate()
        right_side = numbers['root'].number

        i = 10
        for dependency in numbers['root'].left_dependencies:
            n = numbers[dependency]
            #print(f'Checking {n.label}')
            returned_num = numbers[dependency].should_make_it_equal_to(right_side)
            if returned_num and not n.left is None and not n.right is None:
                print(f'Made {n.label} - {n.number} equal to {right_side}. Left side: {numbers[n.left].number}. Right side: {numbers[n.right].number}')
            right_side = returned_num if not returned_num is None else right_side
            if 'humn' == dependency:
                break
            #print(f'Value after: {n.number}')
            #print(f'Value after: {numbers[n.right].number}')
            #break
    
    #print(right_side)
    #print(numbers['vncb'].number)
    #print(numbers['cjhd'].number)
    print(numbers['humn'].number)