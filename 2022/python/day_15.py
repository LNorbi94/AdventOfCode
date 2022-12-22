from dataclasses import dataclass
import re
import threading
from multiprocessing import Process

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

def count_impossible_locations(sensors, x_range):
    global max_x, min_x
    impossible_locations = 0
    for i in x_range:
        for j in range(0, 4000001):
            p = Point(i, j)
            found_bad_sensor = False
            shortest_distance_to_p = None
            closest_sensor = None
            for sensor in sensors:
                distance_to_p = distance(p, sensor.location)
                #print(f'Checking Point ({p.x};{p.y}) and Sensor ({sensor.location.x};{sensor.location.y}). Distance between them is: {distance_to_p}. Distance between Sensor and it\'s beacon is: {sensor.distance_to_beacon}.')
                if distance_to_p <= sensor.distance_to_beacon:
                    #print('Point was closer to the sensor than it\'s beacon.')
                    #print(f'point is {i}, {j}, distance is {distance_to_p} and to beacon: {sensor.distance_to_beacon}')
                    #return impossible_locations
                    found_bad_sensor = True
                else:
                    if shortest_distance_to_p is None or shortest_distance_to_p > distance_to_p:
                        shortest_distance_to_p = distance_to_p
                        closest_sensor = sensor
            
            if j + closest_sensor.distance_to_beacon >= 4000000:
                break
            else:
                j += (closest_sensor.distance_to_beacon - distance(p, closest_sensor.location))
            if not found_bad_sensor:
                print(f'point is {i}, {j}, distance is {distance_to_p} and to beacon: {sensor.distance_to_beacon}')
                print(i * 4000000 + j)
                return Point(i, j)
            else:
                #print(f'You could place a beacon on ({i}, {y}).')
                None
    return None

if __name__ == '__main__':
    with open('/Users/lestarnorbert/rust/advent_of_code/src/day_15.txt') as f:
        input_data = f.readlines()
        import re
        def all_numbers(s): return [int(d) for d in re.findall("(-?\d+)", s)]
        def md(p, q): return abs(p[0]-q[0])+abs(p[1]-q[1])

        data = [all_numbers(line) for line in input_data]
        radius = {(a,b):md((a,b),(c,d)) for (a,b,c,d) in data}
        scanners = radius.keys()

        acoeffs, bcoeffs = set(), set()
        for ((x,y), r) in radius.items():
            acoeffs.add(y-x+r+1)
            acoeffs.add(y-x-r-1)
            bcoeffs.add(x+y+r+1)
            bcoeffs.add(x+y-r-1)

        bound = 4_000_000
        for a in acoeffs:
            for b in bcoeffs:
                p = ((b-a)//2, (a+b)//2)
                if all(0<c<bound for c in p):
                    if all(md(p,t)>radius[t] for t in scanners):
                        print(4_000_000*p[0]+p[1])
        exit(0)
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
            if not beacon in beacons:
                beacons.append(beacon)
            if sensor.x == 8 and sensor.y == 7:
                esensor = Sensor(sensor, beacon)

        #possible_location = (count_impossible_locations(sensors, beacons, 2000000))
        #print(f'Max: {max_x}, Min: {min_x}')
        #exit(0)
        #print(len(beacons))
        #print(len(sensors))
        for i in range(9):
            start = int(i * 4000000 / 8)
            end = int((i + 1) * 4000000 / 8)
            print(f'Start: {start}, end: {end}')
            Process(target=count_impossible_locations, args=(sensors, range(start, end))).start()
