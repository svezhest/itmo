import sys

sys.stdin = open('allvectors.in', 'r')
sys.stdout = open('allvectors.out', 'w')

n = int(input())

bin = [0] * n
rng = range(n - 1, -1, -1)

for i in range(2 ** n):
    for j in rng:
        bin[j] = i % 2
        i //= 2
    print(*bin, sep='')