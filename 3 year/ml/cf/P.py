from math import log

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
xProb = dict()

for (x, y) in xyDict.keys():
    if x not in xProb:
        xProb[x] = 0
    prob = xyDict[(x, y)] / xDict[x]
    xProb[x] -= log(prob) * prob


print(sum(xProb[x] * xDict[x] / n for x in range(k1 + 1) if x in xProb))
