import sys

sys.stdin = open('choose.in', 'r')
sys.stdout = open('choose.out', 'w')

n, m = map(int, input().split())
sett = set()
listt = []


def go(i, j):
    if j == m:
        print(*listt, sep=' ')
        listt.pop()
        return
    for k in range(i, n):
        listt.append(k + 1)
        go(k + 1, j + 1)
    if len(listt) > 0:
        listt.pop()


go(0, 0)
