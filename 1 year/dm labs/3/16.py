import sys

sys.stdin = open('choose2num.in', 'r')
sys.stdout = open('choose2num.out', 'w')

c = [None] * 31
for i in range(31):
    c[i] = [1] + [0] * 30
    for j in range(1, i + 1):
        c[i][j] = c[i - 1][j - 1] + c[i - 1][j]

n, k = map(int, input().split())
per = [int(x) for x in input().split()]

num = 0
prev = 0
for i in range(k):
    for j in range(per[i] - prev - 1):
        num += c[n - i - 1][k - i - 1]
        n -= 1
    prev = per[i]

print(num)
