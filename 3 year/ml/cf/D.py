n, m = map(int, input().split())

xs = []
ys = []

for _ in range(n):
    inp = list(map(int, input().split()))
    x = inp[:-1]
    y = inp[-1]
    xs.append(x + [1])
    ys.append(y)

ws = list(map(int, input().split()))


def dot(a, b):
    return sum(a[i] * b[i] for i in range(min(len(a), len(b))))


def sign(x):
    return -1 if x < 0 else (0 if x == 0 else 1)


def d_smape(y, pred):
    if sign(y) == 0 or sign(pred - y) == 0:
        return 0
    return (sign(y) * abs(pred) + pred) / (((abs(pred) + abs(y)) ** 2) * sign(y) * sign(y - pred))


res = list(dot(ws, x) for x in xs)

smape = list(list(x * d_smape(res[i], ys[i]) for x in xs[i]) for i in range(min(len(ys), len(res))))

for grad in smape:
    print(*grad)
