from math import sqrt, e, pi, cos


def euclidean_dist(row1, row2):
    res = 0.0
    for i in range(len(row1)):
        res += (row1[i] - row2[i]) ** 2
    return sqrt(res)


def manhattan_dist(row1, row2):
    res = 0.0
    for i in range(len(row1)):
        res += abs(row1[i] - row2[i])
    return res


def chebyshev_dist(row1, row2):
    res = 0.0
    for i in range(len(row1)):
        res = max(res, abs(row1[i] - row2[i]))
    return res


distances = {
    'euclidean': euclidean_dist,
    'chebyshev': chebyshev_dist,
    'manhattan': manhattan_dist,
}


def cut(x, func):
    return 0 if abs(x) > 1 else func(x)


kernels = {
    'uniform': lambda u: 0.5 if abs(u) < 1 else 0.0,
    'triangular': lambda u: cut(u, lambda u: 1 - abs(u)),
    'epanechnikov': lambda u: cut(u, lambda u: 0.75 * (1 - u * u)),
    'quartic': lambda u: cut(u, lambda u: 15 / 16 * ((1 - u * u) ** 2)),
    'triweight': lambda u: cut(u, lambda u: 35 / 32 * (1 - u * u) ** 3),
    'tricube': lambda u: cut(u, lambda u: 70 / 81 * (1 - abs(u) ** 3) ** 3),
    'gaussian': lambda u: 1 / sqrt(2 * pi) * e ** (-0.5 * u * u),
    'cosine': lambda u: cut(u, lambda u: pi / 4 * cos(pi / 2 * u)),
    'logistic': lambda u: 1 / (e ** u + 2 + e ** (-u)),
    'sigmoid': lambda u: (2 / pi) * (1 / (e ** u + e ** (-u)))
}

n, m = map(int, input().split())

matrix = []
for i in range(n):
    matrix.append([int(x) for x in input().split()])

xs = []
ys = []
for i in range(n):
    xs.append(matrix[i][:-1])
    ys.append(matrix[i][-1])

target = [int(x) for x in input().split()]
distance_name = input()
kernel_name = input()
window_name = input()
param = int(input())

distance = distances[distance_name]
kernel = kernels[kernel_name]

dist = []
for i in range(n):
    dist.append(distance(target, xs[i]))

if window_name == 'variable':
    temp = sorted(dist)
    param = temp[param]

numerator = 0
denominator = 0

if param != 0:
    for i in range(n):
        k = kernel(dist[i] / param)
        numerator += k * ys[i]
        denominator += k

if denominator != 0:
    print(numerator / denominator)
else:
    same = [ys[i] for i in range(len(dist)) if dist[i] == 0]
    if len(same) != 0:
        print(sum(same) / len(same))
    else:
        print(sum(ys) / n)
