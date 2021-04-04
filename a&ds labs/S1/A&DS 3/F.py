n = int(input())

INF = 5_000_000

inp = [None] * n
dp = [None] * n
hist = [None] * n

for i in range(n):
    inp[i] = int(input())
    dp[i] = [INF] * n
    hist[i] = [[]] * n

if n == 0:
    print(0)
    print(0, 0)
    exit()

if n == 1:
    print(inp[0])
    oAoA = 0
    if inp[0] > 100:
        oAoA = 1
    print(oAoA, 0)
    exit()


if inp[0] > 100:
    dp[0][0] = INF
    dp[0][1] = inp[0]
else:
    dp[0][0] = inp[0]
    dp[0][1] = INF

for i in range(1, n):
    if inp[i] <= 100:
        if dp[i - 1][0] + inp[i] > dp[i - 1][1]:
            dp[i][0] = dp[i - 1][1]
            hist[i][0] = hist[i - 1][1] + [i + 1]
        else:
            dp[i][0] = dp[i - 1][0] + inp[i]
            hist[i][0] = hist[i - 1][0]
    else:
        dp[i][0] = dp[i - 1][1]
        hist[i][0] = hist[i - 1][1] + [i + 1]
    for j in range(1, n - 1):
        if inp[i] > 100:
            if dp[i - 1][j + 1] >= dp[i - 1][j - 1] + inp[i]:
                dp[i][j] = dp[i - 1][j - 1] + inp[i]
                hist[i][j] = hist[i - 1][j - 1]
            else:
                dp[i][j] = dp[i - 1][j + 1]
                hist[i][j] = hist[i - 1][j + 1] + [i + 1]
        else:
            if dp[i - 1][j] + inp[i] > dp[i - 1][j + 1]:
                dp[i][j] = dp[i - 1][j + 1]
                hist[i][j] = hist[i - 1][j + 1] + [i + 1]
            else:
                dp[i][j] = dp[i - 1][j] + inp[i]
                hist[i][j] = hist[i - 1][j]
    if inp[i] > 100:
        dp[i][n - 1] = dp[i - 1][n - 2] + inp[i]
        hist[i][n - 1] = hist[i - 1][n - 1]
    else:
        dp[i][n - 1] = dp[i - 1][n - 1] + inp[i]
        hist[i][n - 1] = hist[i - 1][n - 1]
# print(*dp, sep='\n')
j = 0
while dp[n - 1][j] == INF:
    j += 1
while j < n - 1 and dp[n - 1][j] == dp[n - 1][j + 1]:
    j += 1
print(dp[n - 1][j])
print(j, len(hist[n - 1][j]))
for x in hist[n - 1][j]:
    print(x)