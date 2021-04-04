import sys

sys.stdin = open('gray.in', 'r')
sys.stdout = open('gray.out', 'w')

n = int(input())

bin = [0] * n
rng = range(n - 1, -1, -1)

for i in range(2 ** n):
    i ^= (i >> 1)
    for j in rng:
        bin[j] = i % 2
        i //= 2
    print(*bin, sep='')