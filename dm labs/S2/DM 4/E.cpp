#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <list>
#include <queue>

#define long long long

using namespace std;

bool check(set<int> &cur, list<set<int>> &tommy) {
    for (auto &it : tommy) {
        if (it == cur) {
//            если эта шняга пашет, я люблю плюзы
            return false;
        }
    }
    return true;
}

int main() {
    freopen("problem5.in", "r", stdin);
    freopen("problem5.out", "w", stdout);
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
    int qq_moi_mal4ik[101][26];
    for (int i = 0; i < 101; ++i) {
        for (int c = 0; c < 26; ++c) {
            qq_moi_mal4ik[i][c] = -1;
        }
    }
    for (int i = 0; i < m; ++i) {
        int from, to;
        char c;
        cin >> from >> to >> c;
        q[from - 1][c - 'a'].insert(to - 1);
    }
//    томми
    list<set<int>> tommy;
    map<set<int>, int> new_by_ToMMy;
    set<int> cur = {0};
    new_by_ToMMy[cur] = 0;
    set<int> next;
    tommy.push_back(cur);
    int numeration = 1;
    vector<int> n_t;
    if (t[0]) {
        n_t.push_back(0);
    }
    while (!tommy.empty()) {
        cur = tommy.front();
        tommy.pop_front();
        for (int c = 0; c < 26; ++c) {
            for (int v : cur) {
                next.insert(q[v][c].begin(), q[v][c].end());
            }
            if (next.empty()) {
                continue;
            }
            if (new_by_ToMMy.count(next) == 0) {
                tommy.push_back(next);
                for (int v : next) {
                    if (t[v]) {
                        n_t.push_back(numeration);
                        break;
                    }
                }
                new_by_ToMMy[next] = numeration++;
            }
            qq_moi_mal4ik[new_by_ToMMy[cur]][c] = new_by_ToMMy[next];
            next.clear();
        }
    }

    n = numeration;

    map<int, int> *edges_optim = new map<int, int>[n];
    for (int i = 0; i < n; ++i) {
        edges_optim[i] = map<int, int>();
        for (int c = 0; c < 26; ++c) {
            if (qq_moi_mal4ik[i][c] != -1) {
                ++edges_optim[i][qq_moi_mal4ik[i][c]];
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
            for (auto &u : edges_optim[j]) {
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
    for (int v : n_t) {
        res += dp[l][v];
        res %= 1000000007;
    }
    cout << res;
    return 0;
}