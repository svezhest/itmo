def bingen(seed, arr):
    for _ in range(len(arr)):
        arr[_] = seed % 2
        seed //= 2


L = set()
for size in range(1, 6):
    coefs = [None] * (size + 1)
    varrs = [None] * size
    bintable = [None] * (2 ** size)
    for j in range(2 ** (size + 1)):
        bingen(j, coefs)
        for k in range(2 ** size):
            bingen(k, varrs)
            r = coefs[0]
            for i in range(size):
                r ^= (varrs[i] & coefs[i + 1])
            bintable[k] = r
        L.add(''.join(str(e) for e in bintable))


def checkM(bintable):
    length = len(bintable)
    if length > 1:
        length //= 2
        for i in range(length):
            if bintable[i] > bintable[length + i]:
                return False
        return checkM(bintable[:length]) and checkM(bintable[length:])
    else:
        return True


def checkS(bintable):
    for i in range(len(bintable) // 2):
        if bintable[i] == bintable[-(i + 1)]:
            return False
    return True


n = int(input())

t0 = True
t1 = True
m = True
s = True
l = True

for i in range(n):
    f = input()
    if f[0] == '0':
        if f[2] != '0':
            t0 = False
        if f[-1] != '1':
            t1 = False
        s = False
    else:
        if t0 and f[2] != '0':
            t0 = False
        if t1 and f[-1] != '1':
            t1 = False
        if m and not checkM(list(int(i) for i in f[2:])):
            m = False
        if s and not checkS(f[2:]):
            s = False
        if l and f[2:] not in L:
            l = False
    if not (t0 or t1 or m or s or l):
        break
if not (t0 or t1 or m or s or l):
    print("YES")
else:
    print("NO")
