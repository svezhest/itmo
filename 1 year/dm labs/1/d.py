def check_impl(a, b, bin_size):
    # a <= b ? binary
    for i in range(bin_size):
        if a[i] > b[i]:
            return False
    return True


def neg(a, bin_size):
    c = [None] * bin_size
    for i in range(bin_size):
        c[i] = 1 - a[i]
    return c


def conj(a, b, bin_size):
    c = [None] * bin_size
    for i in range(bin_size):
        c[i] = a[i] & b[i]
    return c


def disj(a, b, bin_size):
    c = [None] * bin_size
    for i in range(bin_size):
        c[i] = a[i] | b[i]
    return c


n = int(input())

numz = [int(x) for x in input().split()]
bin_size = 33

rez = int(input())

nums = [None] * n

for i in range(n):
    seed = numz[i]
    nums[i] = [None] * bin_size
    for j in range(bin_size):
        nums[i][j] = seed % 2
        seed //= 2

res = [None] * bin_size
seed = rez

for j in range(bin_size):
    res[j] = seed % 2
    seed //= 2

answ = ""
answvalue = [0] * bin_size

for j in range(bin_size):
    tansw = ""
    if nums[0][j] == 0:
        t = neg(nums[0], bin_size)
        tansw += "~1"
    else:
        t = nums[0]
        tansw += "1"
    
    for i in range(1, n):
        if nums[i][j] == 0:
            t = conj(t, neg(nums[i], bin_size), bin_size)
            tansw += "&" + "~" + str(i + 1)
        else:
            t = conj(t, nums[i], bin_size)
            tansw += "&" + str(i + 1)
    if check_impl(t, res, bin_size):
        answvalue = disj(answvalue, t, bin_size)
        answ += tansw + "|"

ok = True
for j in range(bin_size):
    if answvalue[j] != res[j]:
        ok = False
        break

if rez == 0:
    print("~1&1")
elif ok:
    print(answ[:-1])
else:
    print("Impossible")
