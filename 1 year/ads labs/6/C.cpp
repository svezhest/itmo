#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

void dfs(int *distance, vector<int> *children, int i, int d) {
    distance[i] = d;
    for (auto &it : children[i]) {
        dfs(distance, children, it, d + 1);
    }
}

int main() {
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    int parents[n];
    int weights[n];
    parents[0] = 0;
    weights[0] = INT_MAX;
    vector<int> children[n];
    for (int i = 1; i < n; ++i) {
        int t;
        cin >> t >> weights[i];
        parents[i] = t - 1;
        children[t - 1].push_back(i);
    }
    int distance[n];
    dfs(distance, children, 0, 0);

    vector<int> ups[n];
    vector<int> mindp[n];
    int d = 0;
    bool flag = true;
//    n log n
    while (flag) {
        flag = false;
        for (int i = 0; i < n; ++i) {
            if (ups[i].empty()) {
                if (i != 0) {
                    flag = true;
                }
                ups[i].push_back(parents[i]);
                mindp[i].push_back(weights[i]);
            } else {
                if (!(i == 0 || ups[i].back() == 0)) {
                    flag = true;
                }
                ups[i].push_back(ups[ups[i][d - 1]][d - 1]);
                mindp[i].push_back(min(mindp[i][d - 1], mindp[ups[i][d - 1]][d - 1]));
            }
        }
        ++d;
    }
    for (int i = 0; i < n; ++i) {
        while (ups[i].size() <= ceil(log2(n))) {
            ups[i].push_back(0);
        }
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, res, a_, b_;
        int min = INT_MAX;
        cin >> a >> b;
        --a;
        --b;
        a_ = a;
        b_ = b;
        if (distance[a] < distance[b]) {
            swap(a, b);
        }
        int D = distance[a] - distance[b];
        for (int k = ceil(log2(n)); k >= 0; --k) {
            if (D >= 1 << k) {
                min = std::min(min, mindp[a][k]);
                a = ups[a][k];
                D -= 1 << k;
            }
        }
        if (a == b) {
            res = a;
            goto got_lca;
        }
        for (int k = ceil(log2(n)); k >= 0; --k) {
            int u, v;
            u = ups[a][k];
            v = ups[b][k];
            if (u != v) {
                min = std::min(min, mindp[a][k]);
                a = u;
                min = std::min(min, mindp[b][k]);
                b = v;
            }
        }
        min = std::min(std::min(min, weights[a]), weights[b]);
        got_lca:
        cout << min << '\n';
    }

    return 0;
}