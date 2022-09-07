k1, k2 = map(int, input().split())
n = int(input())

temp = [list(map(int, input().split())) for _ in range(n)]
X = [x for x, y in temp]
Y = [y for x, y in temp]

xDict = dict()
yDict = dict()
xyDict = dict()


def count(T, tDict):
    for t in T:
        if t in tDict:
            tDict[t] += 1
        else:
            tDict[t] = 1


count(X, xDict)
count(Y, yDict)
count([(x, y) for x, y in temp], xyDict)

ans = sum((val - xDict[x] * yDict[y] / n) ** 2 / (xDict[x] * yDict[y] / n) for ((x, y), val) in xyDict.items())

summ = [0] * (k1 + 1)

for ((x, y), _) in xyDict.items():
    summ[x] += yDict[y]

print(ans + sum((xDict[x] if x in xDict else 0) * (n - summ[x]) / n for x in range(k1 + 1)))

