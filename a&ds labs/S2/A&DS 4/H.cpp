#include <bits/stdc++.h>

using namespace std;

int *mset;
int *mmin;
int nn;

void propagate(int i) {
    if (i > nn - 2) {
        return;
    }
    for (int j = 2 * i + 1; j <= 2 * i + 2; ++j) {
        mset[j] = max(mset[i], mset[j]);
        mmin[j] = mset[j];
    }
}

int fmin(int l, int r, int i, int lx, int rx) {
    if (rx < l || r < lx) {
        return INT_MAX;
    }
    if (l <= lx && rx <= r) {
        return mmin[i];
    }
    propagate(i);
    int ml = (lx + rx) / 2;
    int mr = (lx + rx + 1) / 2;
    auto m1 = fmin(l, r, 2 * i + 1, lx, ml);
    auto m2 = fmin(l, r, 2 * i + 2, mr, rx);
    return min(m1, m2);
}


void fset(int v, int l, int r, int i, int lx, int rx) {
    if (l <= lx && rx <= r) {
        mset[i] = max(v, mset[i]);
        mmin[i] = max(v, mmin[i]);
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
    mset[i] = min(mset[2 * i + 1], mset[2 * i + 2]);
    mmin[i] = min(mmin[2 * i + 1], mmin[2 * i + 2]);
}

int main() {
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    nn = 1 << static_cast<int>(ceil(log2(n)));
    mmin = new int[2 * nn - 1];
    mset = new int[2 * nn - 1];
    for (int i = 0; i < 2 * nn - 1; ++i) {
        mset[i] = INT_MIN;
        mmin[i] = INT_MIN;
    }
    pair<int, int> q[m];
    int v[m];
    for (int j = 0; j < m; ++j) {
        cin >> q[j].first >> q[j].second;
        q[j].first--;
        q[j].second--;
        cin >> v[j];
        fset(v[j], q[j].first, q[j].second, 0, 0, nn - 1);
    }

    for (int j = 0; j < m; ++j) {
        if (fmin(q[j].first, q[j].second, 0, 0, nn - 1) != v[j]) {
            cout << "inconsistent";
            return 0;
        }
    }
    cout << "consistent\n";
    for (int i = 0; i < n; ++i) {
        cout << fmin(i, i, 0, 0, nn - 1) << ' ';
    }
    free(mmin);
    free(mset);
}