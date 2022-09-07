from math import sqrt

n = int(input())
temp = [list(map(int, input().split())) for _ in range(n)]
X = [x for x, y in temp]
Y = [y for x, y in temp]

X_mean = sum(X) / n
Y_mean = sum(Y) / n
dX = [x - X_mean for x in X]
dY = [y - Y_mean for y in Y]
denom = sqrt(sum(dy ** 2 for dy in dY) * sum(dx ** 2 for dx in dX))
res = sum(dx * dy for dx, dy in zip(dX, dY)) / denom if denom != 0 else 0
print(res)
