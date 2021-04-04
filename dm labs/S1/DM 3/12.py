import sys

sys.stdin = open('part2sets.in', 'r')
sys.stdout = open('part2sets.out', 'w')

n, k = map(int, input().split())
ans = [None] * k
for i in range(k):
    ans[i] = []


def print_set():
    for a in ans:
        print(*a, sep=' ')
    print()


def make_sets(x, sets):
    if x == n:
        if sets == k:
            print_set()
        return
    if sets < k:
        ans[sets].append(x + 1)
        make_sets(x + 1, sets + 1)
        ans[sets].pop()
    for i in range(sets):
        ans[i].append(x + 1)
        make_sets(x + 1, sets)
        ans[i].pop()


make_sets(0, 0)
