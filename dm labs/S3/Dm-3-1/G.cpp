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
constexpr int MAXM = 1;
constexpr int MAXK = 1;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<set<int>> edges(n + 1);
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        edges[from].insert(to);
        edges[to].insert(from);
    }

    if (m == n * (n - 1) / 2) {
//        K n
        cout << n << '\n';
        for (int i = 1; i <= n; ++i) {
            cout << i << '\n';
        }
        return 0;
    }

    int k = 0;
    int not_max = 0;

    for (int i = 1; i <= n; ++i) {
        k = max(k, static_cast<int>(edges[i].size()));
    }

    for (int i = 1; i <= n; ++i) {
        if (edges[i].size() != k) {
            not_max = i;
            break;
        }
    }

    queue<int> q;
    vector<int> order;
    vector<bool> visited(n + 1, false);

    q.push(not_max);
    visited[not_max] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.pb(v);
        for (auto u : edges[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }

    if (k % 2 == 0) {
        ++k;
    }

    set<int> free;
    vector<int> colors(n + 1, 0);

    for (int i = 1; i <= k; ++i) {
        free.insert(i);
    }

    for (int i = n - 1; i >= 0; --i) {
        set<int> not_used = free;
        for (auto neighbour : edges[order[i]]) {
            not_used.erase(colors[neighbour]);
        }
        colors[order[i]] = *not_used.begin();
    }

    cout << k << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << colors[i] << '\n';
    }
    return 0;
}