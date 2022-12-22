
def is_tree_visible(forest, i, j):
    print(f'---- Checking for {i}, {j}: {forest[i][j]}')
    # i is 1, j is 2
    # so it's in 2nd row, 3rd column
    # Left side
    visible = True
    for k in range(0, j):
        print(f'Checking {k}, {i}: {forest[i][k]}')
        if forest[i][k] >= forest[i][j]:
            visible = False
            break

    if visible:
        print('Left is cool')
        return True

    visible = True
    # Right side
    for k in range(j + 1, len(forest[i])):
        print(f'Checking {k}, {i}: {forest[i][k]}')
        if forest[i][k] >= forest[i][j]:
            visible = False
            break

    if visible:
        print('Right is cool')
        return True

    visible = True
    # Top side
    for k in range(0, i):
        print(f'Checking {j}, {k}: {forest[k][j]}')
        if forest[k][j] >= forest[i][j]:
            visible = False
            break

    if visible:
        print('Top is cool')
        return True

    visible = True
    # Bottom side
    for k in range(i + 1, len(forest)):
        print(f'Checking {j}, {k}: {forest[j][k]}')
        if forest[k][j] >= forest[i][j]:
            visible = False
            break

    if visible:
        print('Bottom is cool')
        return True

    return False


with open('src/day_8.txt') as f:
    forest = []
    for line in f.readlines():
        forest += [[int(tree) for tree in line.strip()]]
    
    visible_trees = len(forest) * 4 - 4
    for i in range(1, len(forest) - 1):
        for j in range(1, len(forest[i]) - 1):
            if is_tree_visible(forest, i, j):
                visible_trees += 1
    print(visible_trees)
    #print(forest)