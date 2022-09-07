#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 20001;

bool marked[MAXN];
int in[MAXN];
int up[MAXN];
int in_time = 0;
map<int, vector<pair<int, int>>> e{};
vector<int> ans{};

void dfs(int v, int prev) {
    if (marked[v]) {
        return;
    }
    marked[v] = true;
    in[v] = up[v] = in_time++;
    for (auto& p: e[v]) {
        int u = p.first;
        if (u == prev) {
            continue;
        }
        if (!marked[u]) {
            dfs(u, v);
            up[v] = min(up[v], up[u]);
        } else {
            up[v] = min(up[v], in[u]);
        }
    }
}


void dfs2(int v, int prev) {
    if (marked[v]) {
        return;
    }
    marked[v] = true;
    for (auto& p: e[v]) {
        int u = p.first;
        if (u == prev) {
            continue;
        }
        if (!marked[u]) {
            dfs2(u, v);
            if (up[u] == in[u]) {
                ans.push_back(p.second);
            }
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    memset(in, 0, MAXN);
    memset(marked, false, MAXN);
    memset(up, 0, MAXN);
    for (int i = 1; i <= m; ++i) {
        int t1, t2;
        cin >> t1 >> t2;
        e[t1].emplace_back(t2, i);
        e[t2].emplace_back(t1, i);
    }
    for (int i = 1; i <= n; ++i) {
        dfs(i, i);
    }
    memset(marked, false, MAXN);
    for (int i = 1; i <= n; ++i) {
        dfs2(i, i);
    }
    cout << ans.size() << '\n';
    sort(ans.begin(), ans.end());
    for (auto e : ans) {
        cout << e << '\n';
    }
    return 0;
}