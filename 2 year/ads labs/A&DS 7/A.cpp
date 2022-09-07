#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 100001;

int in[MAXN];
deque<int> stk{};
map<int, set<int>> e{};


int main() {
    int n, m;
    cin >> n >> m;
    memset(in, 0, MAXN);
    for (int i = 0; i < m; ++i) {
        int t1, t2;
        cin >> t1 >> t2;
        if (e[t1].find(t2) == e[t1].end()) {
            ++in[t2];
            e[t1].insert(t2);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (in[i] == 0) {
            stk.push_back(i);
        }
    }
    vector<int> ans{};
    for (int i = 0; i < n; ++i) {
        if (stk.empty()) {
            cout << "-1";
            return 0;
        }
        int v = stk.back();
        stk.pop_back();
        ans.push_back(v);
        for (auto u: e[v]) {
            if (--in[u] == 0) {
                stk.push_back(u);
            }
        }
    }
    for (auto i : ans) {
        cout << i << ' ';
    }
    return 0;
}
