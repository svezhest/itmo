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

constexpr int MAXN = e5;
constexpr int MAXM = e5;
constexpr int MAXK = 1;

vector<pair<set<int>, int>> edges;
bool marked[MAXN]{};

int dfs(int v) {
    if (marked[v]) {
        return edges[v].S;
    }
    marked[v] = true;
    set<int> used;
    for (auto u: edges[v].F) {
        used.insert(dfs(u));
    }
    int g = 0;
    while (used.find(g) != used.end()) {
        ++g;
    }
    return edges[v].S = g;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; ++i) {
        edges.pb({{}, 0});
    }
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        edges[from].F.insert(to);
    }
    for (int i = 1; i <= n; ++i) {
        dfs(i);
    }
    for (int i = 1; i <= n; ++i) {
        cout << edges[i].S << '\n';
    }
    return 0;
}