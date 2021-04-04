import sys
from math import *

sys.stdin = open('input.txt', 'r')
sys.stdout = open('output.txt', 'w')


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
    return dot_product(a, b)/(a.len() * b.len())


def vec_check(a, b):
    return a.getx() * b.gety() - a.gety() * b.getx() >= 0


ov = [float(x) for x in input().split()]
if len(ov) == 2:
    ov.append(0)
ov = Vector(ov)
oa = [float(x) for x in input().split()]
if len(oa) == 2:
    oa.append(0)
oa = Vector(oa)
vm = [float(x) for x in input().split()]
prm = vm.copy()
if len(vm) == 2:
    vm.append(1)
    prm.append(0)
prm[2] = 0
vm = Vector(vm)
prm = Vector(prm)
ow = [float(x) for x in input().split()]
if len(ow) == 2:
    ow.append(0)
ow = Vector(ow)

vw = vector_sum(vector_mul_by_k(ov, -1), ow)

beta = 90 - degrees(acos(findcos(vw, oa)))

gamma = asin(prm.len()/vm.len())
if not vec_check(oa, prm):
    gamma *= -1

if abs(beta) > 60 or gamma > 60:
    print(0)
else:
    if vec_check(oa, vw):
        print(1)
    else:
        print(-1)
    print(beta)
    print(gamma)
    print("Let's try english now")

sys.stdin.close()
sys.stdout.close()
