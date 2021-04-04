import sys

sys.stdin = open("input.txt", 'r')
sys.stdout = open("output.txt", 'w')

n, m = map(int, input().split())
inp = [None] * n
dp = [None] * n
for i in range(n):
    inp[i] = [int(x) for x in input().split()]
    dp[i] = [0] * m
for i in range(n):
    for j in range(m):
        if i > 0 and j > 0:
            dp[i][j] = max(dp[i - 1][j] + inp[i][j],
                           dp[i][j - 1] + inp[i][j])
        elif i > 0:
            dp[i][j] = dp[i - 1][j] + inp[i][j]
        elif j > 0:
            dp[i][j] = dp[i][j - 1] + inp[i][j]
        else:
            dp[i][j] = inp[i][j]

i = n - 1
j = m - 1
print(dp[i][j])
ans = []
while i != 0 or j != 0:
    x = dp[i][j] - inp[i][j]
    if i > 0 and dp[i - 1][j] == x:
        i -= 1
        ans.append('D')
    else:
        j -= 1
        ans.append('R')
print(*ans[::-1], sep='')
