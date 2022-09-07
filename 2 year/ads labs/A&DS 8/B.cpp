#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define F first
#define S second
#define pb push_back

constexpr int e4 = 10000;
constexpr int e5 = 100000;
constexpr int e6 = 1000000;
constexpr int e7 = 10000000;
constexpr int e8 = 100000000;
constexpr int e9 = 1000000000;
constexpr ll e10 = 10000000000;

constexpr int MAXN = 3 * e4 + 1;
constexpr int MAXM = 4 * e5 + 1;


int main() {
//    set to sort
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    vector<map<int, int>> e;
    int n, m;
    ll d[MAXN];
    for (long long &i : d) {
        i = e4 * MAXN;
    }
    cin >> n >> m;
    for (int i = 0; i <= n; ++i) {
        e.emplace_back();
    }
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        auto it = e[a].find(b);
        if (it != e[a].end()) {
            if ((*it).S > w) {
                (*it).S = w;
                e[b][a] = w;
            }
        } else {
            e[a][b] = w;
            e[b][a] = w;
        }
    }

    set<int> q{1};
    d[1] = 0;
    while (!q.empty()) {
        auto b = q.begin();
        auto u = *b;
        q.erase(b);
        for (auto &x: e[u]) {
            if (d[u] + x.S < d[x.F]) {
                d[x.F] = d[u] + x.S;
                q.insert(x.F);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << d[i] << ' ';
    }
    return 0;
}