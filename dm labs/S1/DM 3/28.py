import sys

sys.stdin = open('nextmultiperm.in', 'r')
sys.stdout = open('nextmultiperm.out', 'w')

n = int(input())
per = [int(x) for x in input().split()]

boolissimo = [0] * n
maxx = per[-1]
maxi = 0

for i in range(n - 1, -1, -1):
    boolissimo[per[i] - 1] += 1
    if per[i] < maxx:
        maxi = i
        break
    if per[i] > maxx:
        maxx = per[i]
# print(maxi, minn)
j = per[maxi]
while j < n and boolissimo[j] == 0:
    j += 1
if j == n:
    print('0 ' * n)
else:
    boolissimo[j] -= 1
    per[maxi] = j + 1
    j = maxi + 1
    for i in range(n):
        while boolissimo[i] > 0:
            per[j] = i + 1
            j += 1
            boolissimo[i] -= 1
    print(*per)