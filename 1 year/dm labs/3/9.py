import sys

sys.stdin = open('brackets.in', 'r')
sys.stdout = open('brackets.out', 'w')

n = int(input())
ans = []


def go(op, d):
    if op < n:
        ans.append("(")
        go(op + 1, d + 1)
        ans.pop()
    if d > 0:
        ans.append(")")
        go(op, d - 1)
        ans.pop()
    if op == n and d == 0:
        print(*ans, sep='')


go(0, 0)
