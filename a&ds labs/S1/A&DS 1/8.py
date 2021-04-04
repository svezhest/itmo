w, h, n = map(int, input().split())
l = 0
r = max(n * min(w, h), w, h) + 1
while l < r - 1:
    m = l + (r - l) // 2
    if (m // w) * (m // h) >= n:
        side = m
        r = m
    else:
        l = m
print(side)
