from copy import deepcopy
import re
from queue import Queue
from math import ceil

class Valve:
    def __init__(self, name, neighbours, flow_rate) -> None:
        self.name = name
        self.neighbours = neighbours
        self.flow_rate = flow_rate
        self.turned_on = False
        self.paths_to_other_valves = dict()

    def should_be_considered(self):
        return self.flow_rate > 0 and not self.turned_on

    def turn_on(self):
        self.turned_on = True

    def flow_rate_until_end(self, valves, path, time_left):
        remaining_time = time_left
        sum_flow_rate = 0
        best_plan = Queue()

        for p in path:
            valve = valves[p]
            best_plan.put(valve.name)
            if valve.should_be_considered():
                gain_from_valve = (remaining_time - 2) * valve.flow_rate
                if gain_from_valve > self.flow_rate:
                    remaining_time -= 1
                    best_plan.put('Turn On')
                    sum_flow_rate += (remaining_time - 1) * valve.flow_rate
                    print(f'Turning on {valve.name} is a good idea, we will gain {remaining_time * valve.flow_rate} in {remaining_time}.')
            remaining_time -= 1

        remaining_time -= 2
        sum_flow_rate += remaining_time * self.flow_rate
        print(f'With current valve we will gain {remaining_time * self.flow_rate} in {remaining_time}.')
        best_plan.put(self.name)
        best_plan.put('Turn On')
        return (sum_flow_rate, best_plan)

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
                    starting_valve.paths_to_other_valves[neighbour] = path_until_here[1:]
                    print(f'Path to {neighbour} from {starting_valve.name}: {path_until_here[1:]}')

def is_better_plan(plan, flow_rate, new_plan, new_flow_rate, time_left):
    current_plan_rate = flow_rate / (  plan.qsize()) if plan and not plan.empty() else 0
    new_plan_rate = new_flow_rate / (  new_plan.qsize()) if new_plan and not new_plan.empty() else 0
    return new_plan_rate > current_plan_rate

def check_for_better_plan(current_best, current_plan, actual_valve, valves, time_left):
    best_flow_rate = current_best
    best_plan = current_plan

    for v in actual_valve.paths_to_other_valves:
        valve = valves[v]
        if not valve.should_be_considered():
            continue

        (flow_rate, plan) = valve.flow_rate_until_end(valves, actual_valve.paths_to_other_valves[valve.name], time_left)
        print(f'Current valve: {valve.name}. Best flow rate gained: {flow_rate}, plan: {plan.queue}, plan rate: {flow_rate * (time_left - plan.qsize())}.')
        if is_better_plan(best_plan, best_flow_rate, plan, flow_rate, time_left):
            best_flow_rate = flow_rate
            best_plan = plan

    return (best_flow_rate, best_plan)

with open('/Users/lestarnorbert/rust/advent_of_code/src/day_16.txt') as f:
    valves = dict()
    parse_input(f.readlines(), valves)
    determine_paths(valves)

    flow_released = 0
    flow_release_rate = 0
    actual_valve = valves[next(iter(valves))]
    open_valves = []
    best_plan = None
    current_plan_rate = 0

    for i in range(30):
        flow_released += flow_release_rate
        print(f'== Minute {i + 1} ==')
        if not open_valves:
            print('No valves are open.')
        else:
            print(f'Valves {[v.name for v in open_valves]} are open, releasing {flow_release_rate} pressure.')

        (flow_rate, plan) = check_for_better_plan(current_plan_rate, best_plan, actual_valve, valves, 30 - i)
        if is_better_plan(best_plan, current_plan_rate, plan, flow_rate, 30 - i):
            print(f'Found new best plan: {plan.queue}')
            best_plan = plan
            current_plan_rate = flow_rate

        if best_plan and not best_plan.empty():
            next_action = best_plan.get()
            if next_action == 'Turn On':
                print(f'You open Valve {actual_valve.name}.')
                actual_valve.turn_on()
                flow_release_rate += actual_valve.flow_rate
                open_valves.append(actual_valve)
            else:
                print(f'You move to Valve {next_action}.')
                actual_valve = valves[next_action]

            if best_plan.empty():
                current_plan_rate = 0
        else:
            current_plan_rate = 0
            best_plan = None
        print('')

    print(flow_released)