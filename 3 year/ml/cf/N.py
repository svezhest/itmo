k = int(input())
n = int(input())

temp = [list(map(int, input().split())) for _ in range(n)]
X = [x for x, y in temp]
Y = [y for x, y in temp]

y2_mean = sum(y * y for y in Y) / n

x_data = dict()
for x, y in temp:
    if x not in x_data:
        x_data[x] = [y]
    else:
        x_data[x].append(y)

print(y2_mean - sum(sum(ys) ** 2 / len(ys) for ys in x_data.values()) / n)
