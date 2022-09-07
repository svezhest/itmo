n, m = map(int, input().split())
inp = [None] * n
dp = [None] * n
twom = 1 << m
block = [0] * (n + 1)
for i in range(n):
    inp[i] = input()
    dp[i] = [None] * (m + 1)
    for j in range(m):
        dp[i][j] = [0] * twom
        if inp[i][j] == 'X':
            block[i] += 1 << j
    dp[i][m] = [0] * twom

dp[0][0][block[0]] = 1

for i in range(n):
    for j in range(m):
        for p in range(twom):
            if p & (1 << j) != 0:
                dp[i][j + 1][p - (1 << j)] += dp[i][j][p]
            else:
                dp[i][j + 1][p + (1 << j)] += dp[i][j][p]
                if j < m - 1 and p & (1 << (j + 1)) == 0:
                    dp[i][j + 1][p + (1 << (j + 1))] += dp[i][j][p]
    if i < n - 1:
        for p in range(twom):
            if p & block[i + 1] == 0:
                dp[i + 1][0][p | block[i + 1]] = dp[i][m][p]

# for d in dp:
#     print(*d, sep='\n')
#     print()

print(dp[n - 1][m][0])