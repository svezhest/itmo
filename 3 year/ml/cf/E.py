from math import exp, inf
import math


def log(x):
    if x == 0:
        return -inf
    else:
        return math.log(x)


k = int(input())
ls = list(map(float, input().split()))
a = float(input())
n = int(input())

temp = []
word_set = set()
word_id = dict()

for i in range(n):
    temp.append(input().split())
    for w in temp[-1][2:]:
        word_set.add(w)

i = 0
for w in word_set:
    word_id[w] = i
    i += 1

w_size = i

y_count = [[0] * w_size for _ in range(k + 1)]
y_freq = [0] * (k + 1)

for line in temp:
    clazz, x = int(line[0]), line[2:]
    y_freq[clazz] += 1
    for w in set(x):
        y_count[clazz][word_id[w]] += 1

m = int(input())

x_test = [input().split()[1:] for _ in range(m)]
p = [[(y_count[y + 1][w_id] + a) / (y_freq[y + 1] + 2 * a) for w_id in range(w_size)] for y in range(k)]

for x in x_test:
    values = []
    for y in range(k):
        x_ids = [word_id[w] if w in word_id else -1 for w in set(x)]
        p_xy = sum([(log(p[y][w_id]) if w_id in x_ids else log(1 - p[y][w_id])) for w_id in range(w_size)])
        values.append(log(ls[y]) + log(y_freq[y + 1] / n) + p_xy)

    mx = max(values)
    values = [exp(v - mx) if abs(v) >= 1e-4 else 0 for v in values]

    summ = sum(values)
    for y in range(k):
        values[y] /= summ

    print(*values, sep=" ")
