from copy import deepcopy
import re
from queue import Queue
from collections import deque
from dataclasses import dataclass

@dataclass
class Plan:
    destination : str
    steps : deque = deque()
    flow_rate : int = 0
    flow_rate_modifier : int = 1
    length : int = 0
    weighted_distance : int = 1

    def __bool__(self):
        return len(self.steps) > 0

    def rate(self):
        #return (self.flow_rate + self.flow_rate_modifier) / (self.length + self.weighted_distance)
        return self.flow_rate / self.weighted_distance

class Valve:
    def __init__(self, name, neighbours, flow_rate) -> None:
        self.name = name
        self.neighbours = neighbours
        self.flow_rate = flow_rate
        self.turned_on = False
        self.reachable_valves = dict()

    def should_be_considered(self):
        return self.flow_rate > 0 and not self.turned_on

    def turn_on(self):
        self.turned_on = True
    
    def weight(self):
        weight = 1
        for valve in self.reachable_valves:
            if valves[valve].should_be_considered():
                weight += len(self.reachable_valves[valve])
        return weight

    def flow_rate_modifier(self):
        modifier = 0
        for valve in self.reachable_valves:
            if valves[valve].should_be_considered():
                modifier += valves[valve].flow_rate
        return modifier

    def calculated_flow_rate(self, valves, path, time_left, flow_release_rate):
        remaining_time = time_left
        sum_flow_rate = 0
        plan_release_rate = flow_release_rate
        best_plan = deepcopy(Plan(self.name))

        for p in path:
            sum_flow_rate += plan_release_rate
            valve = valves[p]
            best_plan.steps.append(valve.name)
            remaining_time -= 1

        sum_flow_rate += plan_release_rate
        plan_release_rate += self.flow_rate
        sum_flow_rate += plan_release_rate
        remaining_time -= 2
        sum_flow_rate += remaining_time * plan_release_rate
        print(f'With current valve we will gain {sum_flow_rate} in {remaining_time}.')

        best_plan.steps.append(self.name)
        best_plan.steps.append('Turn On')
        best_plan.flow_rate = sum_flow_rate
        best_plan.flow_rate_modifier = valves[self.name].flow_rate_modifier()
        best_plan.length = len(best_plan.steps)
        best_plan.weighted_distance = valves[self.name].weight()
        print(f'Plan is: {best_plan}. Plan\'s rate: {best_plan.rate()}')
        return best_plan

def parse_input(input, valves : dict):
    for line in input:
        label = re.match(r'Valve \w+', line)
        label = label.group()[6:].strip()

        flow_rate = re.findall(r'\d+', line)
        flow_rate = int(flow_rate[0])

        if 'valves' in line:
            neighbours = re.findall(r'valves .*', line)
            neighbours = [n.strip() for n in neighbours[0][7:].split(',')]
        else:
            neighbours = re.findall(r'valve .*', line)
            neighbours = [n.strip() for n in neighbours[0][6:].split(',')]

        valves[label] = Valve(label, neighbours, flow_rate)

def determine_paths(valves : dict):
    for valve in valves:
        starting_valve = valves[valve]
        valves_to_process = Queue()
        valves_to_process.put((starting_valve, []))
        valves_processed = []

        while not valves_to_process.empty():
            (next_valve, path_until_here) = valves_to_process.get()
            valves_processed.append(next_valve.name)

            neighbours = next_valve.neighbours
            path_until_here = deepcopy(path_until_here)
            path_until_here.append(next_valve.name)

            for neighbour in neighbours:
                if not neighbour in valves_processed:
                    valves_to_process.put((valves[neighbour], path_until_here))
                    starting_valve.reachable_valves[neighbour] = path_until_here[1:]
                    print(f'Path to {neighbour} from {starting_valve.name}: {path_until_here[1:]}')

def is_better_plan(plan, new_plan):
    current_plan_rate = plan.rate() if plan else 0
    new_plan_rate = new_plan.rate() if new_plan else 0
    return new_plan_rate > current_plan_rate

def check_for_better_plan(actual_valve, valves, time_left, flow_release_rate):
    best_plan = None

    for v in actual_valve.reachable_valves:
        valve = valves[v]
        if not valve.should_be_considered():
            continue

        plan = valve.calculated_flow_rate(valves, actual_valve.reachable_valves[valve.name], time_left, flow_release_rate)
        if is_better_plan(best_plan, plan):
            best_plan = plan

    return best_plan

with open('../input_files/day_16.txt') as f:
    valves = dict()
    parse_input(f.readlines(), valves)
    determine_paths(valves)

    flow_released = 0
    flow_release_rate = 0
    actual_valve = valves[next(iter(valves))]
    open_valves = []
    best_plan = None

    for i in range(30):
        flow_released += flow_release_rate
        print(f'== Minute {i + 1} ==')
        if not open_valves:
            print('No valves are open.')
        else:
            print(f'Valves {[v.name for v in open_valves]} are open, releasing {flow_release_rate} pressure.')

        plan = check_for_better_plan(actual_valve, valves, 30 - i, flow_release_rate)
        if not best_plan:
            print(f'Found new best plan: {plan}')
            best_plan = plan

        if best_plan:
            next_action = best_plan.steps.popleft()
            if next_action == 'Turn On':
                print(f'You open Valve {actual_valve.name}.')
                actual_valve.turn_on()
                flow_release_rate += actual_valve.flow_rate
                open_valves.append(actual_valve)
            else:
                print(f'You move to Valve {next_action}.')
                actual_valve = valves[next_action]

        print('')

    print(flow_released)