n = int(input())
s = [int(x) for x in input().split()]
dp = [1] * n
maxx = 0
for i in range(n):
    for j in range(i - 1, -1, -1):
        if s[i] > s[j]:
            dp[i] = max(dp[i], dp[j] + 1)
    if dp[i] > maxx:
        maxx = dp[i]
        maxi = i
print(maxx)
i = maxi
ans = []
for j in range(maxx):
    t = dp[i]
    ans.append(s[i])
    i -= 1
    while i >= 0 and dp[i] != t - 1:
        i -= 1
print(*ans[::-1], sep=' ')