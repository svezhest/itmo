import sys

sys.stdin = open('num2brackets2.in', 'r')
sys.stdout = open('num2brackets2.out', 'w')

n, x = map(int, input().split())

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
ans = []
stack = []
bal = 0
for i in range(2 * n - 1, -1, -1):
    c = 0
    if bal < n:
        c = dp[i][bal + 1] * pows[(i - (bal + 1)) >> 1]
    if c >= x + 1:
        ans.append('(')
        stack.append(True)
        bal += 1
        continue
    else:
        x -= c
        c = 0
    if len(stack) > 0 and bal >= 0 and stack[-1]:
        c = dp[i][bal - 1] * pows[(i - bal + 1) >> 1]
    if c >= x + 1:
        ans.append(')')
        stack.pop()
        bal -= 1
        continue
    x -= c
    c = 0
    if bal < n:
        c = dp[i][bal + 1] * pows[(i - (bal + 1)) >> 1]
    if c >= x + 1:
        ans.append('[')
        stack.append(False)
        bal += 1
        continue
    else:
        x -= c
        ans.append(']')
        stack.pop()
        bal -= 1
print(*ans, sep='')
