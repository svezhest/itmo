import sys
from math import *


class Vector:
    def __init__(self, arr):
        self.x = arr[0]
        self.y = arr[1]
        self.z = arr[2]

    def len(self):
        return (dot_product(self, self)) ** 0.5

    def mul_by_k(self, k):
        self.x *= k
        self.y *= k
        self.z *= k

    def __str__(self):
        return "(" + str(self.x) + ", " + str(self.y) + ", " + str(self.z) + ")"

    def getx(self):
        return self.x

    def gety(self):
        return self.y

    def getz(self):
        return self.z


def vector_sum(a, b):
    return Vector([a.x + b.x, a.y + b.y, a.z + b.z])


def vector_mul_by_k(a, k):
    return Vector([a.x * k, a.y * k, a.z * k])


def dot_product(a, b):
    return a.x * b.x + a.y * b.y + a.z * b.z


def cross_product(a, b):
    return Vector([a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x])


def comb_product(a, b, c):
    return dot_product(a, cross_product(b, c))


def findcos(a, b):
    return dot_product(a, b) / (a.len() * b.len())


def is_collinear(a, b):
    return cross_product(a, b) == 0


prec = 12
e = 1e-12


def precision_corr(x):
    if abs(x - round(x, prec)) < e:
        return round(x)
    return x


def vec_precision_corr(x):
    return [precision_corr(el) for el in x]


def gauss_calc_back(m, i, s):
    if len(m) == 0 or i == -1 or s == -1:
        return m
    if m[s][i] != 1:
        return gauss_calc_back(m, s - 1, i - 1)
    for j in range(s - 1, -1, -1):
        first = m[j][i]
        for k in range(i, len(m[j])):
            m[j][k] -= m[s][k] * first
    m = [vec_precision_corr(x) for x in m]
    return gauss_calc_back(m, i - 1, s - 1)


def gauss_calc_forward(m, ind):
    if len(m) == 0 or ind >= len(m[0]):
        return m
    zeros = []
    no_zeros = []
    for s in m:
        if s[ind] == 0:
            zeros.append(s)
        else:
            no_zeros.append(s)
    if len(no_zeros) == 0:
        return gauss_calc_forward(zeros, ind + 1)

    def normalize(a):
        norm = a[ind]
        return [el / norm for el in a]

    no_zeros = [normalize(s) for s in no_zeros]
    no_zeros = [no_zeros[0]] + [[s[i] - no_zeros[0][i] for i in range(len(s))] for s in no_zeros[1:]]
    no_zeros = [vec_precision_corr(x) for x in no_zeros]
    if len(m) == 1:
        return no_zeros + zeros
    return [no_zeros[0]] + gauss_calc_forward(no_zeros[1:] + zeros, ind + 1)


def get_index(m):
    if len(m) == 0:
        return 0
    r = 0
    for el in m[-1]:
        if el != 0:
            break
        r += 1
    return r


def gauss_calc(m):
    m = gauss_calc_forward(m, 0)
    return gauss_calc_back(m, get_index(m), len(m) - 1)


# def cross_line(a, b):
#     gauss = [a, b]
#     t = gauss[0][0]
#     if t == 0:
#         t2 = gauss[1][0]
#         if t2 == 0:
#
#     if t != 0:
#         for i in gauss[0]:
#             gauss[0] /= t

print(*gauss_calc([[0, 1, 2, 3], [0, 6, 5, 1]]), sep='\n')
