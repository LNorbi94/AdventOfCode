def calculate_round_score(enemy_pick, your_pick):
    if enemy_pick == 'A':
        if your_pick == 'X':
            return 3
        elif your_pick == 'Y':
            return 6
        elif your_pick == 'Z':
            return 0
    elif enemy_pick == 'B':
        if your_pick == 'X':
            return 0
        elif your_pick == 'Y':
            return 3
        elif your_pick == 'Z':
            return 6
    elif enemy_pick == 'C':
        if your_pick == 'X':
            return 6
        elif your_pick == 'Y':
            return 0
        elif your_pick == 'Z':
            return 3

def chosen_tool_score(your_pick):
        if your_pick == 'A':
            return 1
        elif your_pick == 'B':
            return 2
        elif your_pick == 'C':
            return 3

def choose_tool(enemy_pick, result):
    if result == 'Y':
        return enemy_pick
    if enemy_pick == 'A':
        if result == 'X':
            return 'C'
        elif result == 'Z':
            return 'B'
    elif enemy_pick == 'B':
        if result == 'X':
            return 'A'
        elif result == 'Z':
            return 'C'
    elif enemy_pick == 'C':
        if result == 'X':
            return 'B'
        elif result == 'Z':
            return 'A'

def result_score(result):
        if result == 'X':
            return 0
        elif result == 'Y':
            return 3
        elif result == 'Z':
            return 6

with open('src/day_2.txt') as f:
    score_sum = 0
    for line in f.readlines():
        enemy_pick = line[0:1]
        result = line[2:3]
        score_sum += chosen_tool_score(choose_tool(enemy_pick, result))
        #print(score_sum)
        score_sum += result_score(result)

    print(score_sum)