import sys

sys.stdin = open('perm2num.in', 'r')
sys.stdout = open('perm2num.out', 'w')

n = int(input())
per = [int(x) for x in input().split()]

boolissimo = [0] * n
fact = [1]
for i in range(1, n):
    fact.append(fact[i - 1] * i)

ans = 0
for p in range(n):
    s = 0
    for i in range(per[p] - 1):
        if boolissimo[i] == 0:
            s += 1
    boolissimo[per[p] - 1] = 1
    ans += fact[n - p - 1] * s

print(ans)