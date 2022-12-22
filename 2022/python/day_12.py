from dijkstra import *


def get_neighbours(vertices, i, j):
    neighbours = []
    if i > 0:
        neighbours.append((i - 1, j))
    if i + 1 < len(vertices):
        neighbours.append((i + 1, j))
    if j > 0:
        neighbours.append((i, j - 1))
    if j + 1 < len(vertices[i]):
        neighbours.append((i, j + 1))
    return neighbours


def get_elevation(square):
    if square == 'S':
        return get_elevation('a')
    if square == 'E':
        return get_elevation('z')
    return ord(square) - 97


def can_go_to_neighbour(vertex, neighbour):
    return get_elevation(neighbour) - get_elevation(vertex) <= 1


with open('src/day_12.txt') as f:
    vertices = []
    for line in f.readlines():
        vertex_line = []
        for vertex in line.strip():
            vertex_line.append(vertex)
        vertices.append(vertex_line)

    v = []
    end_idx = 0
    s = []
    for i in range(len(vertices)):
        for j in range(len(vertices[i])):
            n = Node(i * len(vertices) + j)
            #print(f'Node: {i}, {j}. Idx in vertices: {i * len(vertices[i]) + j}')
            for neighbour in get_neighbours(vertices, i, j):
                if can_go_to_neighbour(vertices[i][j], vertices[neighbour[0]][neighbour[1]]):
                    n.Add_child(neighbour[0] * len(vertices[i]) + neighbour[1], 1)
            v.append(n)
            if vertices[i][j] == 'E':
                end_idx = i * len(vertices[i]) + j
            if vertices[i][j] == 'S' or vertices[i][j] == 'a':
                s.append(i * len(vertices[i]) + j)

    #exit(0)
    #print(len(v))
    best_distance = 9000
    for start in s:
        path = [0 for i in range(len(v))]
        dist = dijkstraDist(v, start, path)
    
        # Loop to print the distance of
        # every node from source vertex
        for i in range(len(dist)):
            if (dist[i] == infi):
                #print(f'{i} and {s} are not connected')
                continue
            if i == end_idx:
                print("Distance of {}th vertex from source vertex {} is: {}".format(
                                i, start, dist[i]))
                if dist[i] < best_distance:
                    best_distance = dist[i]
    
    print(best_distance)