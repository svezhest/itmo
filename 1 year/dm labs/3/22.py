import sys

sys.stdin = open('part2num.in', 'r')
sys.stdout = open('part2num.out', 'w')

inp = [int(x) for x in input().split('+')]
n = sum(inp)

p = [None] * (n + 1)
p[0] = [1] * (n + 2)
for i in range(1, n + 1):
    p[i] = [0] * (n + 2)
for i in range(1, n + 1):
    p[i][i] = 1
    s = 1
    for j in range(i - 1, 0, -1):
        if i - j >= j:
            p[i][j] = p[i - j][j]
        s += p[i][j]
    for j in range(i):
        s -= p[i][j]
        p[i][j] += s
# print(*p, sep='\n')
for i in range(n + 1):
    for j in range(1, n + 1):
        p[i][j] = p[i][0] - p[i][j]
    p[i][0] = 0
# print(*p, sep='\n')
def find(n, i):
    if n != 0:
        if i == 0:
            x = 0
        else:
            x = inp[i - 1]
        return find(n - inp[i], i + 1) + p[n][inp[i]] - p[n][x]
    return 0

print(find(n, 0))