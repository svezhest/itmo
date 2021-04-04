import sys

sys.stdin = open('brackets2num2.in', 'r')
sys.stdout = open('brackets2num2.out', 'w')

line = input()
n = len(line) // 2

pows = [0] * (n + 1)
pows[0] = 1
for i in range(1, n + 1):
    pows[i] = pows[i - 1] << 1

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
bal = 0
ans = 0
stack = []
for i in range(2 * n):
    i_rev = 2 * n - 1 - i
    if line[i] == '(':
        stack.append(True)
        bal += 1
        continue
    if bal < n:
        ans += dp[i_rev][bal + 1] * pows[(i_rev - bal - 1) >> 1]
    if line[i] == ')':
        stack.pop()
        bal -= 1
        continue
    if len(stack) > 0 and stack[-1]:
        ans += dp[i_rev][bal - 1] * pows[(i_rev - bal + 1) >> 1]
    if line[i] == '[':
        bal += 1
        stack.append(False)
        continue
    if bal < n:
        ans += dp[i_rev][bal + 1] * pows[(i_rev - bal - 1) >> 1]
    stack.pop()
    bal -= 1
print(ans)
