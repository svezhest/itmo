def biterize(x, m):
    res = []
    for _ in range(m):
        res.append(x % 2)
        x //= 2
    return res


m = int(input())

ys_true = []
ys_false = []

for i in range(2 ** m):
    y = int(input())
    ys_true.append(y)
    ys_false.append(1 - y)

y_true_count = sum(ys_true)
y_false_count = sum(ys_false)

# constant False
if y_true_count == 0:
    print(1)
    print(1)
    print(*([0] * m + [-1]))
# constant True
elif y_false_count == 0:
    print(1)
    print(1)
    print(*([0] * m + [1]))
else:
    print(2)
    if y_true_count > 512:
        count = y_false_count
        sign = -1
        bit = 0
    else:
        count = y_true_count
        sign = 1
        bit = 1

    print(count, 1)
    for i in range(2 ** m):
        if ys_true[i] == bit:
            bits = biterize(i, m)
            for b in bits:
                print(1 if b == 1 else -10, end=' ')
            print(0.9 - sum(bits))

    print(*([sign] * count), end=' ')
    print(-0.1 * sign)
