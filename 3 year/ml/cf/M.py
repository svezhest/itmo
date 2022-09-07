def vec_sum(A, B):
    return [a + b for a, b in zip(A, B)]


def distance(arr):
    lenn = len(arr)
    arr.sort()
    d = [0, sum(arr) - arr[0]]
    res = 0
    for i, j in zip(list(range(lenn - 1)), list(range(lenn - 1, -1, -1))):
        res += (arr[i] * i) + (d[1] - d[0]) - (j * arr[i])
        d = vec_sum(d, [arr[i], - arr[i + 1]])

    res += arr[-1] * (lenn - 1) + d[1] - d[0]
    return res


k = int(input())
n = int(input())

temp = [list(map(int, input().split())) for _ in range(n)]
X = [x for x, y in temp]
Y = [y for x, y in temp]

classes = dict()
for x, y in temp:
    if y not in classes:
        classes[y] = [x]
    else:
        classes[y].append(x)

inSum = sum(distance(c) for c in classes.values())
outSum = distance(X) - inSum

print(*list(map(int, [inSum, outSum])), sep='\n')
