#include <bits/stdc++.h>

using namespace std;

void num2per(int num, int n, long long *fast_fact) {
    if (num < 0 || num >= fast_fact[n]) {
        while (n--) {
            cout << "0 ";
        }
        cout << '\n';
        return;
    }
    bool boolissimo[n];
    memset(boolissimo, 0, n);
    for (int col = n - 1; col > 0; col--) {
        int t = (num / fast_fact[col]) % (col + 1);
        int tt = 0;
        while (boolissimo[tt]) tt++;
        while (t--)
            while (boolissimo[++tt]);
        boolissimo[tt] = 1;
        cout << tt + 1 << ' ';
    }
    int tt = 0;
    while (boolissimo[tt]) tt++;
    cout << tt + 1 << '\n';
}

int main() {
//    freopen("nextperm.in", "r", stdin);
//    freopen("nextperm.out", "w", stdout);
    int n;
    cin >> n;
    long long fast_fact[n + 1];
    fast_fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fast_fact[i] = i * fast_fact[i - 1];
    int per[n];
    for (int j = 0; j < n; ++j) {
        cin >> per[j];
    }
    bool boolissimo[n];
    memset(boolissimo, 0, n);
    int ans = 0;
    for (int p = 0; p < n; ++p) {
        int s = 0;
        for (int i = 0; i < per[p] - 1; ++i) {
            s += boolissimo[i] ? 0 : 1;
        }
        boolissimo[per[p] - 1] = 1;
        ans += fast_fact[n - p - 1] * s;
    }
    num2per(ans - 1, n, fast_fact);
    num2per(ans + 1, n, fast_fact);
    return 0;
}
