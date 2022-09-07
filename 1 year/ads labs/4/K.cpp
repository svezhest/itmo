#include <bits/stdc++.h>

using namespace std;

void exit(int *a, int n, int i, int lx, int rx) {
    if (lx > rx) {
        return;
    }
    a[i]++;
    if (lx == rx) {
        return;
    }
    if (n <= (rx + lx) / 2) {
        exit(a, n, 2 * i + 1, lx, (rx + lx) / 2);
    } else {
        exit(a, n, 2 * i + 2, 1 + (rx + lx) / 2, rx);
    }
}

int enter(int *a, int n, int i, int lx, int rx) {
    if (n < lx || rx < n) {
        return -2;
    }
    if (a[i] == 0) {
        return -1;
    }
    if (lx == rx) {
        a[i]--;
        return lx;
    }
    int t = enter(a, n, 2 * i + 1, lx, (rx + lx) / 2);
    if (t < 0) {
        if (t == -1) {
            n = (lx + rx) / 2 + 1;
        }
        t = enter(a, n, 2 * i + 2, 1 + (lx + rx) / 2, rx);
    }
    if (t >= 0) {
        a[i]--;
    }
    return t;
}

int enterLoop(int *a, int n, int i, int lx, int rx) {
    int t = enter(a, n, i, lx, rx);
    if (t != -1) {
        return t;
    }
    return enter(a, 0, i, lx, rx);
}

void build(int *a, int i, int lx, int rx) {
    if (rx < lx) {
        return;
    }
    a[i] = rx - lx + 1;
    if (rx == lx) {
        return;
    }
    build(a, 2 * i + 1, lx, (lx + rx) / 2);
    build(a, 2 * i + 2, 1 + (lx + rx) / 2, rx);

}

int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    int nn = 1 << (int) ceil(log(n) / log(2));
    int a[2 * nn - 1];
    build(a, 0, 0, n - 1);
    for (int i = 0; i < m; ++i) {
        string s;
        int ar;
        cin >> s >> ar;
        if (s[1] == 'n') {
            cout << enterLoop(a, ar - 1, 0, 0, n - 1) + 1 << '\n';
        } else {
            exit(a, ar - 1, 0, 0, n - 1);
        }
    }
}