#include <bits/stdc++.h>

using namespace std;

long long *mset;
long long *madd;
long long *mmin;
int nn;

void propagate(int i) {
    if (i > nn - 2) {
        return;
    }
    if (mset[i] != LONG_LONG_MAX) {
        for (int j = 1; j <= 2; ++j) {
            mset[2 * i + j] = mset[i] + madd[i];
            madd[2 * i + j] = 0;
            mmin[2 * i + j] = mset[i] + madd[i];
        }
        mset[i] = LONG_LONG_MAX;
        madd[i] = 0;
    } else {
        for (int j = 1; j <= 2; ++j) {
            madd[2 * i + j] += madd[i];
            mmin[2 * i + j] += madd[i];
        }
        madd[i] = 0;
    }
}

void fadd(long long v, int l, int r, int i, int lx, int rx) {
    propagate(i);
    if (l <= lx && rx <= r) {
        mmin[i] += v;
        madd[i] += v;
        return;
    }
    if (l > rx || lx > r) {
        return;
    }
    long long ml = (lx + rx) / 2;
    long long mr = (lx + rx + 1) / 2;
    fadd(v, l, r, 2 * i + 1, lx, ml);
    fadd(v, l, r, 2 * i + 2, mr, rx);
    mmin[i] = min(mmin[2 * i + 1], mmin[2 * i + 2]);

}

long long fmin(int l, int r, int i, int lx, int rx) {
    propagate(i);
    if (rx < l || r < lx) {
        return LONG_LONG_MAX;
    }
    if (l <= lx && rx <= r) {
        return mmin[i];
    }
    long long ml = (lx + rx) / 2;
    long long mr = (lx + rx + 1) / 2;
    return min(fmin(l, r, 2 * i + 1, lx, ml), fmin(l, r, 2 * i + 2, mr, rx));
}


void fset(long long v, int l, int r, int i, int lx, int rx) {
    propagate(i);
    if (l <= lx && rx <= r) {
        mset[i] = v;
        madd[i] = 0;
        mmin[i] = v;
        return;
    }
    if (l > rx || lx > r) {
        return;
    }
    long long ml = (lx + rx) / 2;
    long long mr = (lx + rx + 1) / 2;
    fset(v, l, r, 2 * i + 1, lx, ml);
    fset(v, l, r, 2 * i + 2, mr, rx);
    mmin[i] = min(mmin[2 * i + 1], mmin[2 * i + 2]);
}

int main() {
    int n;
    cin >> n;
    nn = 1 << (long long) ceil(log2(n));
    mmin = new long long[2 * nn - 1];
    mset = new long long[2 * nn - 1];
    madd = new long long[2 * nn - 1];
    for (int i = 0; i < 2 * nn - 1; ++i) {
        mmin[i] = LONG_LONG_MAX;
        mset[i] = LONG_LONG_MAX;
        madd[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        fset(t, i, i, 0, 0, nn - 1);
    }

    string s;
    while (cin >> s) {
        int ar1, ar2, ar3;
        switch (s[0]) {
            case 's':
                cin >> ar1 >> ar2 >> ar3;
                fset(ar3, ar1 - 1, ar2 - 1, 0, 0, nn - 1);
                break;
            case 'a':
                cin >> ar1 >> ar2 >> ar3;
                fadd(ar3, ar1 - 1, ar2 - 1, 0, 0, nn - 1);
                break;
            case 'm':
                cin >> ar1 >> ar2;
                cout << fmin(ar1 - 1, ar2 - 1, 0, 0, nn - 1) << '\n';
        }
    }
}