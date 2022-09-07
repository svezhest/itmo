#include <bits/stdc++.h>

using namespace std;

long long sum(long long *a, long long l, long long r, long long x, long long lx, long long rx) {
    if (l > r) {
        long long t = l;
        l = r;
        r = t;
    }
    if (rx < l || r < lx) {
        return 0;
    }
    if (l <= lx && rx <= r) {
        return a[x];
    }
    long long ml = (lx + rx) / 2;
    long long mr = (lx + rx + 1) / 2;
    return sum(a, l, r, 2 * x + 1, lx, ml) + sum(a, l, r, 2 * x + 2, mr, rx);
}

void sett(long long *a, long long i, long long v, long long x, long long lx, long long rx) {
    if (rx - lx <= 1) {
        a[x] = v;
        return;
    }
    long long m = (lx + rx + 1) / 2;
    if (i < m) {
        sett(a, i, v, 2 * x + 1, lx, m);
    } else {
        sett(a, i, v, 2 * x + 2, m, rx);
    }
    a[x] = a[2 * x + 1] + a[2 * x + 2];
}

int main() {
    long long n;
    cin >> n;
    long long nn = 1 << (long long) ceil(log(n) / log(2));
    auto *a = new long long[2 * nn - 1];
    memset(a, 0, (2 * nn - 1) * sizeof(long long));
    for (long long i = 0; i < n; ++i) {
        long long t;
        cin >> t;
        sett(a, i, t, 0, 0, nn - 1);
    };
    string s;
    while (cin >> s) {
        long long ar1, ar2;
        cin >> ar1 >> ar2;
        if (s[1] == 'u') {
            cout << sum(a, ar1 - 1, ar2 - 1, 0, 0, nn - 1) << '\n';
        } else {
            sett(a, ar1 - 1, ar2, 0, 0, nn - 1);
        }
    }
}