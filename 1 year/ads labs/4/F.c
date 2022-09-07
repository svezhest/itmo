#include <stdio.h>
#include <stdlib.h>

#define long long long

long min(long a, long b) {
    return a < b ? a : b;
}

long max(long a, long b) {
    return a > b ? a : b;
}

int main() {
    int n, m, u, v;
    long a0, r;
    scanf("%d %d %lld", &n, &m, &a0);
    scanf("\n%d %d", &u, &v);
    long *a = malloc(sizeof(long) * n);
    long *plog = malloc(sizeof(long) * (n + 1));
    {
        int k = 0;
        long pk = 1;
        for (int d = 0; d <= n; ++d) {
            if (pk * 2 <= d) {
                k++;
                pk *= 2;
            }
            plog[d] = k;
        }
    }
    a[0] = a0;
    for (int i = 1; i < n; ++i) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }
    long **tb = malloc(sizeof(long *) * n);
    for (int i = 0; i < n; ++i) {
        tb[i] = malloc(sizeof(long) * (plog[n] + 1));
    }
    for (int i = 0; i < n; ++i) {
        tb[i][0] = a[i];
    }
    for (int k = 1; k <= plog[n]; ++k) {
        for (int i = 0; i <= n - (1 << k); ++i) {
            tb[i][k] = min(tb[i][k - 1], tb[i + (1 << (k - 1))][k - 1]);
        }
    }
    {
        int k = plog[max(v, u) - min(v, u)];
        r = min(tb[min(u, v) - 1][k], tb[max(u, v) - (1 << k)][k]);
    }
    for (int i = 1; i < m; ++i) {
        u = ((17 * u + 751 + r + 2 * i) % n) + 1;
        v = ((13 * v + 593 + r + 5 * i) % n) + 1;
        int k = plog[max(v, u) - min(v, u)];
        r = min(tb[min(u, v) - 1][k], tb[max(u, v) - (1 << k)][k]);
    }
    printf("%d %d %lld", u, v, r);
    free(a);
    for (int i = 0; i < n; ++i) {
        free(tb[i]);
    }
    free(tb);
    free(plog);
    return 0;
}