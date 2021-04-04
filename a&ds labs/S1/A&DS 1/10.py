from math import sqrt


def hypotenuse(a, b):
    return sqrt(a ** 2 + b ** 2)


v1, v2 = map(int, input().split())
border = float(input())
l = 0
h = 1
for i in range(10_000):
    x1 = l + (h - l) / 3
    x2 = l + 2 * (h - l) / 3
    time1 = hypotenuse(x1, 1 - border) / v1 + \
            hypotenuse(1 - x1, border) / v2
    time2 = hypotenuse(x2, 1 - border) / v1 + \
            hypotenuse(1 - x2, border) / v2
    if time1 < time2:
        h = x2
    else:
        l = x1
print(x1)
