import sys

sys.stdin = open('chaincode.in', 'r')
sys.stdout = open('chaincode.out', 'w')

n = int(input())
d = 0
nn = 2 ** n
result = [None] * nn
result[0] = d
for i in range(1, nn):
    d2 = (d << 1) % nn
    d1 = d2 + 1
    if d1 not in result:
        d = d1
    else:
        d = d2
    result[i] = d

rng = range(n - 1, -1, -1)
bin = [None] * n
for x in result:
    for j in rng:
        bin[j] = x % 2
        x //= 2
    print(*bin, sep='')
