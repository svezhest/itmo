a = input()
b = input()

n = len(a) + 1
m = len(b) + 1

dp = [None] * n
for i in range(n):
    dp[i] = [None] * m

for i in range(n):
    for j in range(m):
        if i == 0:
            if j == 0:
                dp[i][j] = 0
            else:
                dp[i][j] = j
        elif j == 0:
            dp[i][j] = i
        elif a[i - 1] == b[j - 1]:
            dp[i][j] = dp[i - 1][j - 1]
        else:
            dp[i][j] = min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]) + 1

print(dp[n - 1][m - 1])
