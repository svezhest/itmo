n = int(input())
temp = [list(map(int, input().split())) for _ in range(n)]


def make_dict(arr):
    t = dict()
    for i in range(len(arr)):
        t[arr[i]] = i
    return t


X = make_dict(sorted([x for x, y in temp]))
Y = make_dict(sorted([y for x, y in temp]))
print(1 - 6 * (sum((X[v[0]] - Y[v[1]]) ** 2 for v in temp)) / (n * n * n - n))
