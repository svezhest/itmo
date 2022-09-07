#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 20001;

bool marked[MAXN];
bool is_cut_vx[MAXN];
//set<int> ans{};
int in[MAXN];
int up[MAXN];
int in_time = 0;
int cut_vx_cnt = 0;
map<int, vector<int>> e{};


void dfs(int v, int prev) {
    if (marked[v]) {
        return;
    }
    marked[v] = true;
    in[v] = up[v] = in_time++;
    int subtree_cnt = 0;
    for (auto u: e[v]) {
        if (u == prev) {
            continue;
        }
        if (!marked[u]) {
            ++subtree_cnt;
            dfs(u, v);
            up[v] = min(up[v], up[u]);
            if (up[u] >= in[v] && !is_cut_vx[v] &&  v != prev) {
//                no escape from this subtree
                is_cut_vx[v] = true;
                ++cut_vx_cnt;
            }
        } else {
            up[v] = min(up[v], in[u]);
        }
    }
    if (v == prev) {
//        root
        if (subtree_cnt >= 2) {
//            has more than 2 children
            ++cut_vx_cnt;
            is_cut_vx[v] = true;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    memset(in, 0, MAXN);
    memset(marked, false, MAXN);
    memset(is_cut_vx, false, MAXN);
    memset(up, 0, MAXN);
    for (int i = 1; i <= m; ++i) {
        int t1, t2;
        cin >> t1 >> t2;
        e[t1].push_back(t2);
        e[t2].push_back(t1);
    }
    for (int i = 1; i <= n; ++i) {
        dfs(i, i);
    }
//    sort(ans.begin(), ans.end());
    cout << cut_vx_cnt << '\n';
    for (int v = 1; v <= n; ++v) {
        if (is_cut_vx[v]) {
            cout << v << ' ';
        }
    }
    return 0;
}