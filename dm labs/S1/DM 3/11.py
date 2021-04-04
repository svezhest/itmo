import sys

sys.stdin = open('subsets.in', 'r')
sys.stdout = open('subsets.out', 'w')

n = int(input())
ans = []

print()


def razb(t):
    for i in range(t + 1, n + 1):
        ans.append(i)
        print(*ans)
        razb(i)
        ans.pop()


razb(0)
