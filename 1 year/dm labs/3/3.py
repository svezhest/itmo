import sys

sys.stdin = open('antigray.in', 'r')
sys.stdout = open('antigray.out', 'w')


def trin(x, sz):
    a = [None] * sz
    for _ in range(sz):
        a[_] = x % 3
        x //= 3
    return a[::-1]


def shift(a):
    for i in range(len(a)):
        a[i] = (a[i] + 1) % 3


n = int(input())

for _ in range(3 ** (n - 1)):
    a = trin(_, n)
    for __ in range(3):
        print(*a, sep='')
        shift(a)