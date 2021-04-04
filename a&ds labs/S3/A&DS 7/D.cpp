#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 20001;

bool marked[MAXN];
int in[MAXN];
int up[MAXN];
int in_time = 0;
map<int, multiset<int>> e{};
vector<int> ans{};
int comp[MAXN];
int comp_cnt = 2;
deque<int> stk{};
int n;

void print_cmp() {
    for (int i = 1; i <= n; ++i) {
        cout << comp[i] << ' ';
    }
}

void dfs(int v, int prev) {
    if (marked[v]) {
        return;
    }
    marked[v] = true;
    in[v] = up[v] = in_time++;
    for (auto u: e[v]) {
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
    stk.push_back(v);
    marked[v] = true;
    for (auto u: e[v]) {
        if (u == prev) {
            continue;
        }
        if (!marked[u]) {
            dfs2(u, v);
            if (up[u] == in[u]) {
//                bridge
                if (e[v].count(u) != 1) {
                    continue;
                }
                int t = stk.back();
                while (t != u) {
                    stk.pop_back();
                    comp[t] = comp_cnt;
                    t = stk.back();
                }
                stk.pop_back();
                comp[t] = comp_cnt;
//                print_cmp();
//                cout << '\n';
                ++comp_cnt;
            }
        }
    }
}

int main() {
    int m;
    cin >> n >> m;
    memset(in, 0, MAXN);
    memset(marked, false, MAXN);
    memset(up, 0, MAXN);
    for (int i = 1; i <= m; ++i) {
        int t1, t2;
        cin >> t1 >> t2;
        if (t1 != t2) {
            e[t1].insert(t2);
            e[t2].insert(t1);
        }
    }
    for (int i = 1; i <= n; ++i) {
        dfs(i, i);
    }
    memset(marked, false, MAXN);
    int root_comp = 1;
    for (int i = 1; i <= n; ++i) {
        dfs2(i, i);
        if (!stk.empty()) {
            while (!stk.empty()) {
                comp[stk.back()] = root_comp;
                stk.pop_back();
            }
            root_comp = comp_cnt++;
        }
    }
    cout << root_comp - 1 << '\n';
    print_cmp();
    return 0;
}
