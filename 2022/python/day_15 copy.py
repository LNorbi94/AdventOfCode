from dataclasses import dataclass
import re

max_x = 0
min_x = 0

@dataclass
class Point:
    x: int
    y: int

def distance(p1, p2):
    return abs(p1.x - p2.x) + abs(p1.y - p2.y)

def check_for_boundary(p):
    global max_x, min_x
    if p.x > max_x:
        max_x = p.x
    if p.x < min_x:
        min_x = p.x

def check_for_boundary_2(p, added_distance = 0):
    p_copy = Point(p.x - added_distance, p.y)
    check_for_boundary(p_copy)
    p_copy = Point(p.x + added_distance, p.y)
    check_for_boundary(p_copy)

class Sensor:
    def __init__(self, point, beacon) -> None:
        self.location = point
        self.beacon = beacon
        self.distance_to_beacon = distance(point, beacon)

def count_impossible_locations(sensors, beacons, y):
    global max_x, min_x
    impossible_locations = 0
    for i in range(min_x, max_x + 1):
        p = Point(i, y)
        found_bad_sensor = False
        for sensor in sensors:
            distance_to_p = distance(p, sensor.location)
            #print(f'Checking Point ({p.x};{p.y}) and Sensor ({sensor.location.x};{sensor.location.y}). Distance between them is: {distance_to_p}. Distance between Sensor and it\'s beacon is: {sensor.distance_to_beacon}.')
            if distance_to_p <= sensor.distance_to_beacon:
                #print('Point was closer to the sensor than it\'s beacon.')
                found_bad_sensor = True
                break
        if found_bad_sensor and p not in beacons:
            impossible_locations += 1
        else:
            print(f'You could place a beacon on ({i}, {y}).')
    return impossible_locations

if __name__ == '__main__':
    with open('/Users/lestarnorbert/rust/advent_of_code/src/day_15.txt') as f:
        lines = f.readlines()
        # Sensor at x=2, y=18: closest beacon is at x=-2, y=15
        sensors = []
        beacons = []
        esensor = None
        for line in lines:
            positions = re.findall('-?[0-9]+', line)
            sensor = Point(int(positions[0]), int(positions[1]))
            beacon = Point(int(positions[2]), int(positions[3]))
            check_for_boundary_2(sensor, distance(sensor, beacon))
            check_for_boundary(beacon)
            sensors.append(Sensor(sensor, beacon))
            if beacon.y == 2000000:
                beacons.append(beacon)
            if sensor.x == 8 and sensor.y == 7:
                esensor = Sensor(sensor, beacon)

        print(count_impossible_locations(sensors, beacons, 2000000))
        exit(0)
        # 8,7hez mi nincs kozel?
        drawing = "               1    1    2    2\n     0    5    0    5    0    5\n"
        for j in range(min_x, max_x):
            drawing += '{0:02}'.format(j) + ' '
            for i in range(-2, 22):
                print(f'{i}, {j}')
                p = Point(i, j)
                distance_to_p = distance(p, esensor.location)
                if i == esensor.beacon.x and j == esensor.beacon.y:
                    drawing += 'B'
                elif i == esensor.location.x and j == esensor.location.y:
                    drawing += 'S'
                elif distance_to_p <= esensor.distance_to_beacon:
                    drawing += '#'
                else:
                    drawing += '.'
            drawing += '\n'
        
        print(drawing)
