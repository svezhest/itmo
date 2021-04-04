import sys

sys.stdin = open('nextperm.in', 'r')
sys.stdout = open('nextperm.out', 'w')


n = int(input())
per = [int(x) for x in input().split()]
perr = per.copy()

boolissimo = [1] * n
minn = per[-1]
maxx = per[-1]
mini = 0
maxi = mini

for i in range(n - 1, -1, -1):
    boolissimo[perr[i] - 1] = 0
    if perr[i] > minn:
        mini = i
        break
    if perr[i] < minn:
        minn = perr[i]

j = perr[mini] - 2
while j > -1 and boolissimo[j] == 1:
    j -= 1
if j == -1:
    print('0 ' * n)
else:
    boolissimo[j] = 1
    perr[mini] = j + 1
    j = mini + 1
    for i in range(n - 1, -1, -1):
        if boolissimo[i] == 0:
            perr[j] = i + 1
            j += 1
    print(*perr)

boolissimo = [1] * n


for i in range(n - 1, -1, -1):
    boolissimo[per[i] - 1] = 0
    if per[i] < maxx:
        maxi = i
        break
    if per[i] > maxx:
        maxx = per[i]
# print(maxi, minn)
j = per[maxi]
while j < n and boolissimo[j] == 1:
    j += 1
if j == n:
    print('0 ' * n)
else:
    boolissimo[j] = 1
    per[maxi] = j + 1
    j = maxi + 1
    for i in range(n):
        if boolissimo[i] == 0:
            per[j] = i + 1
            j += 1
    print(*per)