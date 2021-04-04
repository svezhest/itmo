import sys

sys.stdin = open('partition.in', 'r')
sys.stdout = open('partition.out', 'w')

n = int(input())
ans = []


def razb(t, d):
    for i in range(t, d + 1):
        ans.append(i)
        razb(i, d - i)
        if i == d:
            print(*ans, sep='+')
        ans.pop()


razb(1, n)
