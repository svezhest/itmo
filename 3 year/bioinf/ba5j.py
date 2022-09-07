OP_COST = 11
EXT_COST = 1


def calculate_affine_gap(str_1, str_2, blosum, alphab):
    matrix = [[(0, 'x', 0)] * (len(str_2) + 1) for _ in range(len(str_1) + 1)]
    always_down = [[(-OP_COST + EXT_COST, 0)] * (len(str_2) + 1) for _ in range(len(str_1) + 1)]
    always_right = [[(-OP_COST + EXT_COST, 0)] * (len(str_2) + 1) for _ in range(len(str_1) + 1)]
    for i in range(1, len(str_1) + 1):
        for j in range(1, len(str_2) + 1):

            go_down_now = (matrix[i - 1][j][0] - OP_COST, 1)
            continue_down = (always_down[i - 1][j][0] - EXT_COST, always_down[i - 1][j][1] + 1)
            always_down[i][j] = max(go_down_now, continue_down)
            down = (always_down[i][j][0], 'd', always_down[i][j][1])
            go_right_now = (matrix[i][j - 1][0] - OP_COST, 1)
            continue_right = (always_right[i][j - 1][0] - EXT_COST, always_right[i][j - 1][1] + 1)
            always_right[i][j] = max(go_right_now, continue_right)
            right = (always_right[i][j][0], 'r', always_right[i][j][1])
            straight = (matrix[i - 1][j - 1][0] + blosum[alphab.index(str_1[i - 1])][alphab.index(str_2[j - 1])], 's', 0)
            matrix[i][j] = max(straight, right, down)

    answ_1 = []
    answ_2 = []

    i = len(str_1)
    j = len(str_2)

    # print(*always_right, sep='\n')
    debug_scores = []
    while i != 0 and j != 0:
        if matrix[i][j][1] == 's' or i == 1 and j == 1:
            debug_scores.append(matrix[i][j][0])
            answ_1.append(str_1[i - 1])
            answ_2.append(str_2[j - 1])
            i -= 1
            j -= 1
        elif matrix[i][j][1] == 'r' or i == 1:
            for _ in range(matrix[i][j][2]):
                debug_scores.append(matrix[i][j][0])
                answ_1.append('-')
                answ_2.append(str_2[j - 1])
                j -= 1
        elif matrix[i][j][1] == 'd' or j == 1:
            for _ in range(matrix[i][j][2]):
                debug_scores.append(matrix[i][j][0])
                answ_1.append(str_1[i - 1])
                answ_2.append('-')
                i -= 1
        else:
            print('err')
    answ_1.reverse()
    answ_2.reverse()

    # print(debug_scores)

    print(matrix[-1][-1][0])
    print("".join(answ_1))
    print("".join(answ_2))


# def calculate_penalty(str_1, str_2):
#     assert(len(str_1) == len(str_2))
#     opened_1 = False
#     opened_2 = False
#     score = 0
#     debug_scores = []
#     for i in range(len(str_1)):
#         if str_1[i] == '-':
#             if opened_1:
#                 score -= EXT_COST
#             else:
#                 score -= OP_COST
#             opened_1 = True
#             opened_2 = False
#         elif str_2[i] == '-':
#             if opened_2:
#                 score -= EXT_COST
#             else:
#                 score -= OP_COST
#             opened_2 = True
#             opened_1 = False
#         else:
#             score += blosum[alphab.index(str_1[i])][alphab.index(str_2[i])]
#             opened_1 = False
#             opened_2 = False
#         debug_scores.append(score)
#     debug_scores.reverse()
#     print(debug_scores)
#     return score

with open("blosum62.txt", 'r') as f:
    alphab = f.readline().rstrip().split()
    blosum = [list(map(int, line.rstrip().split()[1:])) for line in f.readlines()]

with open("rosalind_ba5j.txt", 'r') as f:
    str_1 = f.readline().rstrip()
    str_2 = f.readline().rstrip()

calculate_affine_gap(str_1, str_2, blosum, alphab)
