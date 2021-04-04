def distance(a, b):
    return abs(a - b)


n, k = map(int, input().split())
data = list(map(int, input().split()))
queries = list(map(int, input().split()))

for q in queries:
    l = -1
    r = n
    while l < r - 1:
        m = (l + r) // 2
        t = data[m]
        if q < t:
            r = m
        else:
            l = m
    # q is close to r or close to l (?)
    # -1 <= l < r <= n + 1
    if r < n - 1:
        if distance(data[r + 1], q) <= distance(t, q):
            t = data[r + 1]
    if r < n:
        if distance(data[r], q) <= distance(t, q):
            t = data[r]
    if -1 < l:
        if distance(data[l], q) <= distance(t, q):
            t = data[l]
    if 0 < l:
        if distance(data[l - 1], q) <= distance(t, q):
            t = data[l - 1]
    print(t)
