import sys

sys.stdin = open('telemetry.in', 'r')
sys.stdout = open('telemetry.out', 'w')

n, k = map(int, input().split())

pows = [0] * (n + 1)
pows[0] = 1
for i in range(1, n + 1):
    pows[i] = pows[i - 1] * k

gray = [None] * (pows[n])
for i in range(pows[n]):
    gray[i] = [0] * n

for j in range(n):
    add = -1
    x = 0
    for i in range(pows[n]):
        if i % pows[j] == 0:
            if (i / pows[j]) % k == 0:
                add *= -1
            else:
                x += add
        gray[i][n - j - 1] = x

for i in range(pows[n]):
    print(*gray[i], sep='')