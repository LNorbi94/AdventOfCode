
def tree_scenic_score(forest, i, j):
    print(f'---- Checking for {i}, {j}: {forest[i][j]}')
    left_score = 0
    for k in range(j - 1, -1, -1):
        left_score += 1
        if forest[i][k] >= forest[i][j]:
            break

    # Right side
    right_score = 0
    for k in range(j + 1, len(forest[i])):
        right_score += 1
        if forest[i][k] >= forest[i][j]:
            break

    # Top side
    top_score = 0
    for k in range(i - 1, -1, -1):
        top_score += 1
        print(f'Checking {k}, {j}: {forest[k][j]}')
        if forest[k][j] >= forest[i][j]:
            break

    # Bottom side
    bottom_score = 0
    for k in range(i + 1, len(forest)):
        bottom_score += 1
        if forest[k][j] >= forest[i][j]:
            break

    print(f'{left_score}, {right_score}, {bottom_score}, {top_score}')
    return left_score * right_score * bottom_score * top_score


with open('src/day_8.txt') as f:
    forest = []
    for line in f.readlines():
        forest += [[int(tree) for tree in line.strip()]]
    
    best_score = 0
    for i in range(1, len(forest) - 1):
        for j in range(1, len(forest[i]) - 1):
            if tree_scenic_score(forest, i, j) > best_score:
                best_score = tree_scenic_score(forest, i, j)
    print(best_score)
    #print(forest)