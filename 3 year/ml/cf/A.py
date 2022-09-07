n, m, k = map(int, input().split())
obj = list(map(lambda x: int(x) - 1, input().split()))

classes = []
for i in range(m):
    classes.append(list())
for i in range(n):
    classes[obj[i]].append(i + 1)

ans = []
for i in range(k):
    ans.append(list())

moving = 0
for i in range(m):
    while len(classes[i]) % k != 0:
        ans[moving].append(classes[i].pop())
        moving = (moving + 1) % k
    j = 0
    while len(classes[i]) > 0:
        ans[j].append(classes[i].pop())
        j = (j + 1) % k

for a in ans:
    print(len(a), *a)
