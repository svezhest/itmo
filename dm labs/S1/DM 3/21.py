import sys

sys.stdin = open('num2part.in', 'r')
sys.stdout = open('num2part.out', 'w')

n, k = map(int, input().split())

# p[n][k] кол-во разбиений n, 1 число >= k
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
ans = []


def find(nn, kk):
    if len(ans) == 0:
        x = 1
    else:
        x = ans[-1] + 1
    j = x - 1
    for j in range(x, nn + 1):
        if p[nn][j - 1] - p[nn][j] <= kk:
            kk -= p[nn][j - 1] - p[nn][j]
        else:
            j -= 1
            ans.append(j)
            find(nn - j, kk)
            return
    ans.append(j)


find(n, k)
print(*ans, sep='+')
