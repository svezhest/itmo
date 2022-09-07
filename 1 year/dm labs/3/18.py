import sys

sys.stdin = open('brackets2num.in', 'r')
sys.stdout = open('brackets2num.out', 'w')

line = input()
n = len(line) // 2

dp = [None] * (2 * n + 1)
for i in range(2 * n + 1):
    dp[i] = [0] * (n + 1)
dp[0][0] = 1
for i in range(1, 2 * n + 1):
    dp[i][0] = dp[i - 1][1]
    for j in range(1, n):
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1]
    dp[i][n] = dp[i - 1][n - 1]

bal = 0
ans = 0
for i in range(2 * n - 1, -1, -1):
    if bal < n:
        if line[2 * n - 1 - i] == '(':
            bal += 1
            continue
        else:
            ans += dp[i][bal + 1]
    bal -= 1
print(ans)
