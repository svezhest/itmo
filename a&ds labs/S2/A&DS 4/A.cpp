#include "stdio.h"
#include "stdlib.h"

int main() {
    long long b16 = 1 << 16;
    long long b30 = 1 << 30;
    int n, m, b0;
    long long x = 0, y = 0, a0 = 0, z = 0, t = 0;
    scanf("%d", &n);
    scanf("%lld", &x);
    scanf("%lld", &y);
    scanf("%lld", &a0);
    long long *sum = (long long *) malloc(sizeof(long long) * (n + 1));
    sum[0] = 0;
    sum[1] = a0;
    for (int i = 1; i < n; i++) {
        int a = (x * a0 + y) % b16;
        sum[i + 1] = sum[i] + a;
        a0 = a;
    }
    scanf("%d", &m);
    scanf("%lld", &z);
    scanf("%lld", &t);
    scanf("%d", &b0);
    int b;
    long long s = 0;
    for (int i = 1; i < 2 * m; i++) {
        b = (b30 + z * b0 + t) % b30;
        if (i % 2 == 1) {
            int t1 = (b0 + n) % n;
            int t2 = (b + n) % n;
            int minn, maxx;
            if (t1 > t2) {
                minn = t2;
                maxx = t1;
            } else {
                minn = t1;
                maxx = t2;
            }
            if (maxx > n - 1) {
                maxx = n - 1;
            }
            s += sum[++maxx] - (minn > 0 ? sum[minn] : 0);
        }
        b0 = b;
    }
    printf("%lld", s);
    return 0;
}