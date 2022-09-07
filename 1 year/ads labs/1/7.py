n, a, b = map(int, input().split())

n -= 1
a, b = min(a, b), max(a, b)

# 9 3 4
# 8 3
# 8 3*5 + 4*3

# m * a == (n - m) * b

mintime = n * a
l = -1
r = n + 1
m = l
prev = r
while prev != m:
    prev = m
    m = l + (r - l) // 2
    atime = m * a
    btime = (n - m) * b
    delta = atime - btime
    mintime = min(mintime, max(atime, btime))
    if delta == 0:
        break
    if delta < 0:
        l = m
    else:
        r = m
print(mintime + a)
