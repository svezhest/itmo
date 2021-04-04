import sys

sys.stdin = open('nextchoose.in', 'r')
sys.stdout = open('nextchoose.out', 'w')

n, k = map(int, input().split())
per = [int(x) for x in input().split()]

for i in range(k - 1, -1, -1):
    if per[i] + 1 <= n - k + i + 1:
        per[i] += 1
        for j in range(i + 1, k):
            per[j] = per[j - 1] + 1
        print(*per)
        exit(0)
print(-1)