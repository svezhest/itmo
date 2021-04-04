import sys

sys.stdin = open('num2choose.in', 'r')
sys.stdout = open('num2choose.out', 'w')

n, k, m = map(int, input().split())
nn = n
f = [1] * (n + 1)
for i in range(1, n + 1):
    f[i] = f[i - 1] * i


def cnt_c(n, k):
    return f[n] // (f[k] * f[n - k])


for i in range(k):
    while m - cnt_c(n - 1, k - 1) >= 0:
        m -= cnt_c(n - 1, k - 1)
        n -= 1
    print(nn - n + 1, end=' ')
    k -= 1
    n -= 1
