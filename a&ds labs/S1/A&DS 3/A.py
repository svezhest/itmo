import sys

sys.stdin = open('input.txt', 'r')
sys.stdout = open('output.txt', 'w')

n, k = map(int, input().split())
profit = [0] + [int(x) for x in input().split()] + [0]
dp = [-10001] * n
dp[0] = 0

for i in range(n):
    for j in range(1, min(k + 1, n - i)):
        dp[i + j] = max(dp[i + j], dp[i] + profit[i + j])

ans = []
d = n - 1
ans.append(d + 1)
while d > 0:
    x = dp[d] - profit[d]
    d -= 1
    while dp[d] != x:
        d -= 1
    ans.append(d + 1)

print(dp[n - 1])
print(len(ans) - 1)
print(*ans[::-1])