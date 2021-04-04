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

constexpr int MAXN = e5 + 1;
constexpr int MAXM = e5 + 1;
constexpr int MAXK = 1;

vector<pair<vector<int>, bool>> edges;
bool marked[MAXN]{};

void dfs(int v) {
    if (marked[v]) {
        return;
    }
    marked[v] = true;
    for (auto &u: edges[v].F) {
        dfs(u);
        if (!edges[u].S) {
//            if we see a lose
            edges[v].S = true;
//            it is an opportunity to win
        }
    }
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 0; i < MAXN; ++i) {
        edges.emplace_back(1, false);
    }
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        edges[from].F.pb(to);
    }
    dfs(s);
    cout << (edges[s].S? "First" : "Second") << " player wins";
    return 0;
}