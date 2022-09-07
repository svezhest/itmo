#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void dfs(int *distance, vector<int> *children, int i, int d) {
    distance[i] = d;
    for (auto &it : children[i]) {
        dfs(distance, children, it, d + 1);
    }
}

int main() {
    int n;
    cin >> n;
    int parents[n];
    parents[0] = 0;
    vector<int> children[n];
    for (int i = 1; i < n; ++i) {
        int t;
        cin >> t;
        parents[i] = t - 1;
        children[t - 1].push_back(i);
    }
    int distance[n];
    dfs(distance, children, 0, 0);

    vector<int> ups[n];
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
            } else {
                if (!(i == 0 || ups[i].back() == 0)) {
                    flag = true;
                }
                ups[i].push_back(ups[ups[i].back()][d - 1]);
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
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        if (distance[a] < distance[b]) {
            swap(a, b);
        }
        int D = distance[a] - distance[b];
        for (int k = ceil(log2(n)); k >= 0; --k) {
            if (D >= 1 << k) {
                a = ups[a][k];
                D -= 1 << k;
            }
        }
        if (a == b) {
            cout << a + 1 << '\n';
            continue;
        }
        for (int k = ceil(log2(n)); k >= 0; --k) {
            int u, v;
            u = ups[a][k];
            v = ups[b][k];
            if (u != v) {
                a = u;
                b = v;
            }
        }
        cout << ups[a][0] + 1 << '\n';
    }

    return 0;
}