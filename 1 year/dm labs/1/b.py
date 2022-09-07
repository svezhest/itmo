n, k = map(int, input().split())
horn = [None] * k
count = [0] * k
for i in range(k):
    horn[i] = [int(x) for x in input().split()]
    for lit in horn[i]:
        if lit != -1:
            count[i] += 1
stop = False
for _ in range(k):
    has_single = False
    for i in range(k):
        if count[i] == 1:
            has_single = True
            for j in range(n):
                if horn[i][j] != -1:
                    for ii in range(k):
                        if count[ii] == 0:
                            continue
                        if horn[ii][j] != -1:
                            if horn[ii][j] == horn[i][j]:
                                count[ii] = 0
                            else:
                                if count[ii] == 1:
                                    stop = True
                                    break
                                else:
                                    horn[ii][j] = -1
                                    count[ii] -= 1
                    break
            break
    if stop or not has_single:
        break
if stop:
    print("YES")
else:
    print("NO")
