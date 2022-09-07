from math import sqrt

C = float(input())
l = 0
r = sqrt(C)
for i in range(10_000_000):
    x = (l + r) / 2
    t = x * x + sqrt(x)
    if t == C:
        break
    elif t > C:
        r = x
    else:
        l = x
print(x)
