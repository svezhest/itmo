import sys

sys.stdin = open('num2brackets.in', 'r')
sys.stdout = open('num2brackets.out', 'w')

n, x = map(int, input().split())
dp = [None] * (2 * n + 1)
for i in range(2 * n + 1):
    dp[i] = [0] * (n + 1)
dp[0][0] = 1
for i in range(1, 2 * n + 1):
    dp[i][0] = dp[i - 1][1]
    for j in range(1, n):
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1]
    dp[i][n] = dp[i - 1][n - 1]
# print(*dp, sep='\n')
ans = ''
bal = 0
for i in range(2 * n - 1, -1, -1):
    if bal < n:
        if x - dp[i][bal + 1] >= 0:
            x -= dp[i][bal + 1]
        else:
            ans += '('
            bal += 1
            continue
    ans += ')'
    bal -= 1
print(ans)
