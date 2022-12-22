import re
from copy import deepcopy
from dataclasses import dataclass
from math import floor
from enum import Enum

class Robot(Enum):
    ORE = 1
    CLAY = 2
    OBSIDIAN = 3
    GEODE = 4
    NONE = 5

@dataclass
class Cost:
    ore : int = 0
    clay : int = 0
    obsidian : int = 0

class Factory:
    def __init__(self, id, ore_robot_cost, clay_robot_cost, obsidian_robot_cost, geode_robot_cost) -> None:
        self.id = id

        self.ore = 0
        self.clay = 0
        self.obsidian = 0
        self.open_geodes = 0

        self.ore_robot = 1
        self.clay_robot = 0
        self.obsidian_robot = 0
        self.geode_robot = 0

        self.ore_robot_cost = ore_robot_cost
        self.clay_robot_cost = clay_robot_cost
        self.obsidian_robot_cost = obsidian_robot_cost
        self.geode_robot_cost = geode_robot_cost

        self.time = 0

    def continue_work(self):
        self.time += 1

        print(f'== Minute {self.time} ==')

        robot = self.choose_robot()
        if robot is not Robot.NONE:
            print(f'Spend {self.get_cost(robot)} to start building a {robot}.')
        self.collect_rocks(True)
        self.build_robot(robot)

        print('\n')

        return self.time < 24

    def build_robot(self, robot):
        if robot is Robot.ORE:
            self.ore_robot += 1
        elif robot is Robot.CLAY:
            self.clay_robot += 1
        elif robot is Robot.OBSIDIAN:
            self.obsidian_robot += 1
        elif robot is Robot.GEODE:
            self.geode_robot += 1

        if not robot is Robot.NONE:
            self.spend_ores(self.get_cost(robot))

    def get_cost(self, robot):
        if robot is Robot.ORE:
            return self.ore_robot_cost
        elif robot is Robot.CLAY:
            return self.clay_robot_cost
        elif robot is Robot.OBSIDIAN:
            return self.obsidian_robot_cost
        elif robot is Robot.GEODE:
            return self.geode_robot_cost
        return None


    def choose_robot(self):
        if self.ore >= self.geode_robot_cost.ore and self.obsidian >= self.geode_robot_cost.obsidian:
            return Robot.GEODE

        if self.obsidian < self.geode_robot_cost.obsidian:
            return self.obsidian_needed()

        return self.ore_needed()

    def spend_ores(self, cost):
        self.ore -= cost.ore
        self.clay -= cost.clay
        self.obsidian -= cost.obsidian

    def ore_needed(self):
        return Robot.NONE

    def obsidian_needed(self):
        potential_now = deepcopy(self).potential_geodes_opened(0, 0)
        potential_with_new_robot = deepcopy(self).potential_geodes_opened(1, 0)

        if potential_now < potential_with_new_robot or self.obsidian_robot == 0:
            if self.ore >= self.obsidian_robot_cost.ore and self.clay >= self.obsidian_robot_cost.clay:
                return Robot.OBSIDIAN

            if self.clay < self.obsidian_robot_cost.clay:
                return self.clay_needed()

            if self.ore < self.obsidian_robot_cost.ore:
                return self.ore_needed()

        return Robot.NONE

    def clay_needed(self):
        left = deepcopy(self)
        potential_now = left.potential_geodes_opened(0, 0)
        right = deepcopy(self)
        potential_with_new_robot = right.potential_geodes_opened(9999, 1)

        if left.obsidian_robot < right.obsidian_robot or self.clay_robot == 0:
            if self.ore >= self.clay_robot_cost.ore:
                return Robot.CLAY

            if self.ore < self.clay_robot_cost.ore:
                return self.ore_needed()

        return Robot.NONE

    def potential_geodes_opened(self, buy_obsidian_robot, buy_clay_robot):
        while self.time < 25:
            self.time += 1

            robots = self.buildable_robots()
            self.collect_rocks()

            if Robot.GEODE in robots:
                self.geode_robot += 1
                self.build_robot(Robot.GEODE)
            elif Robot.OBSIDIAN in robots and buy_obsidian_robot > 0:
                self.obsidian_robot += 1
                self.build_robot(Robot.OBSIDIAN)
                buy_obsidian_robot -= 1
            elif Robot.CLAY in robots and buy_clay_robot > 0:
                self.clay_robot += 1
                self.build_robot(Robot.CLAY)
                buy_clay_robot -= 1

        return self.open_geodes

    def buildable_robots(self):
        robots = []

        if self.ore >= self.ore_robot_cost.ore:
            robots.append(Robot.ORE)
        if self.ore >= self.clay_robot_cost.ore:
            robots.append(Robot.CLAY)
        if self.ore >= self.obsidian_robot_cost.ore and self.clay >= self.obsidian_robot_cost.clay:
            robots.append(Robot.OBSIDIAN)
        if self.ore >= self.geode_robot_cost.ore and self.obsidian >= self.geode_robot_cost.obsidian:
            robots.append(Robot.GEODE)

        return robots

    def collect_rocks(self, print_text = False):
        self.ore += self.ore_robot
        if print_text:
            print(f'{self.ore_robot} ore-collecting robot(s) collects {self.ore_robot} ore; you now have {self.ore} ore.')
        self.clay += self.clay_robot
        if print_text:
            print(f'{self.clay_robot} clay-collecting robot(s) collects {self.clay_robot} clay; you now have {self.clay} clay.')
        self.obsidian += self.obsidian_robot
        if print_text:
            print(f'{self.obsidian_robot} obsidian-collecting robot(s) collects {self.obsidian_robot} obsidian; you now have {self.obsidian} obsidian.')
        self.open_geodes += self.geode_robot
        if print_text:
            print(f'{self.geode_robot} geode-cracking robot(s) cracks {self.geode_robot} geode; you now have {self.open_geodes} open geode.')

    def print_result(self):
        print(f'Blueprint quality: {self.id * self.open_geodes}')

with open('/Users/lestarnorbert/rust/advent_of_code/src/day_19.txt') as f:
    factories = []
    for line in f.readlines():
        blueprint = [int(n) for n in re.findall(r'[0-9]+', line)]
        blueprint_id = blueprint[0]
        ore_robot_cost = Cost(ore=blueprint[1])
        clay_robot_cost = Cost(ore=blueprint[2])
        obsidian_robot_cost = Cost(ore=blueprint[3], clay=blueprint[4])
        geode_robot_cost = Cost(ore=blueprint[5], obsidian=blueprint[6])
        factories.append(Factory(blueprint_id, ore_robot_cost, clay_robot_cost, obsidian_robot_cost, geode_robot_cost))

    for factory in factories:
        while factory.continue_work():
            None
        factory.print_result()