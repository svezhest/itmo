#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

#define long long long

using namespace std;

int main() {
    freopen("problem4.in", "r", stdin);
    freopen("problem4.out", "w", stdout);
    int n, m, k, l;
    cin >> n >> m >> k >> l;
    bool t[n];
    for (int i = 0; i < n; ++i) {
        t[i] = false;
    }
    for (int i = 0; i < k; ++i) {
        int tmp;
        cin >> tmp;
        t[tmp - 1] = true;
    }
    set<int> q[n][26];
    for (int i = 0; i < m; ++i) {
        int from, to;
        char c;
        cin >> from >> to >> c;
        q[from - 1][c - 'a'].insert(to - 1);
    }

    map<int, int> *edges_optim = new map<int, int>[n];
    for (int i = 0; i < n; ++i) {
        edges_optim[i] = map<int, int>();
        for (int c = 0; c < 26; ++c) {
            for (int v : q[i][c]) {
//                бред или фича?
                ++edges_optim[i][v];
            }
        }
    }
//    for (int i = 0; i < n; ++i) {
//        for (auto v : edges_optim[i]) {
//            cout << i << ' ' << v.first << ' ' << v.second << '\n';
//        }
//    }
    long dp[l + 1][n];
    for (int i = 0; i < l + 1; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < n; ++j) {
            for (auto u : edges_optim[j]) {
                dp[i + 1][u.first] += dp[i][j] * u.second;
                dp[i + 1][u.first] %= 1000000007;
            }
        }
//        cout << i + 1 << '\n';
//        for (int j = 0; j < n; ++j) {
//            cout << dp[i + 1][j] << ' ';
//        } cout << '\n';
    }
    long res = 0;
    for (int i = 0; i < n; ++i) {
        if (t[i]) {
            res += dp[l][i];
            res %= 1000000007;
        }
    }
    cout << res;
    return 0;
}