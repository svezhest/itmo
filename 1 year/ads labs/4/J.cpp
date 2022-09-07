#include <bits/stdc++.h>

#define long long long
using namespace std;

long *mset;
pair<int, long> *mmin;
int nn;

void propagate(int i) {
    if (i > nn - 2) {
        return;
    }
    for (int j = 2 * i + 1; j <= 2 * i + 2; ++j) {
        mset[j] = max(mset[i], mset[j]);
        mmin[j].second = max(mset[j], mmin[i].second);
    }
}

pair<int, long> fmin(int l, int r, int i, int lx, int rx) {
    propagate(i);
    if (rx < l || r < lx) {
        return {l, LONG_LONG_MAX};
    }
    if (l <= lx && rx <= r) {
        return mmin[i];
    }
    int ml = (lx + rx) / 2;
    int mr = (lx + rx + 1) / 2;
    auto m1 = fmin(l, r, 2 * i + 1, lx, ml);
    auto m2 = fmin(l, r, 2 * i + 2, mr, rx);
    return m1.second < m2.second ? m1 : m2;
}


void fset(long v, int l, int r, int i, int lx, int rx) {
    if (l <= lx && rx <= r) {
        mset[i] = max(v, mset[i]);
        mmin[i].second = max(v, mmin[i].second);
        return;
    }
    if (l > rx || lx > r) {
        return;
    }
    propagate(i);
    int ml = (lx + rx) / 2;
    int mr = (lx + rx + 1) / 2;
    fset(v, l, r, 2 * i + 1, lx, ml);
    fset(v, l, r, 2 * i + 2, mr, rx);
    mmin[i] = mmin[2 * i + 1].second < mmin[2 * i + 2].second ? mmin[2 * i + 1] : mmin[2 * i + 2];
    mset[i] = min(mset[2 * i + 1], mset[2 * i + 2]);
}

int main() {
    int n, m;
    cin >> n >> m;
    nn = 1 << static_cast<int>(ceil(log2(n)));
    mmin = new pair<int, long>[2 * nn - 1];
    mset = new long[2 * nn - 1];
    for (int i = 0; i < 2 * nn - 1; ++i) {
        mset[i] = 0;
    }
    for (int i = 0; i < nn; ++i) {
        mmin[i + nn - 1] = {i, 0};
    }
    for (int i = nn - 2; i >= 0; --i) {
        mmin[i] = mmin[2 * i + 1];
    }

    for (int j = 0; j < m; ++j) {
        string s;
        cin >> s;
        int ar1, ar2;
        long ar3;
        switch (s[0]) {
            case 'd':
                cin >> ar1 >> ar2 >> ar3;
                fset(ar3, ar1 - 1, ar2 - 1, 0, 0, nn - 1);
                break;
            case 'a':
                cin >> ar1 >> ar2;
                auto m1 = fmin(ar1 - 1, ar2 - 1, 0, 0, nn - 1);
                cout << m1.second << ' '
                     << m1.first + 1 << '\n';
        }
    }
    free(mmin);
    free(mset);
}