n, m = map(int, input().split())
n, m = max(n, m), min(n, m)
twom = 2 ** (m + 1)

dp = [None] * n
for i in range(n):
    dp[i] = [None] * (m + 1)
    for j in range(m + 1):
        dp[i][j] = [0] * twom
for p in range(twom):
    dp[0][0][p] = 1

for i in range(n):
    for j in range(m):
        for p in range(twom):
            for b in range(2):
                if j == 0 or (p >> (j - 1)) & 7 != b * 7:
                    q = (p & ~(1 << j)) | (b << j)
                    dp[i][j + 1][q] += dp[i][j][p]
    if i < n - 1:
        for p in range(twom):
            q = (p & ~(1 << m)) << 1
            dp[i + 1][0][q] += dp[i][m][p]

print(max(dp[n - 1][m]))
