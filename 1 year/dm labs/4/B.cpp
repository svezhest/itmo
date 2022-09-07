#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    freopen("problem2.in", "r", stdin);
    freopen("problem2.out", "w", stdout);
    unordered_map<int, vector<int>> q;
    int n, m, k;
    string s;
    cin >> s;
    cin >> n >> m >> k;
    bool t[n];
    for (int i = 0; i < n; ++i) {
        t[i] = false;
    }
    for (int i = 0; i < k; ++i) {
        int tmp;
        cin >> tmp;
        t[tmp - 1] = true;
    }
    for (int i = 0; i < m; ++i) {
        int from, to;
        char c;
        cin >> from >> to >> c;
        int p = (from - 1) * 100 + c - 'a';
//        why map doesn't have a 'contains' function?
        if (q.count(p)) {
            q[p].push_back(to - 1);
        } else {
            q[p] = {to - 1};
        }
    }
    int len = s.length() + 1;
    bool can[len][n];
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < n; ++j) {
            can[i][j] = false;
        }
    }
    can[0][0] = true;
    for (int i = 0; i < len - 1; ++i) {
        int c = s[i] - 'a';
        for (int j = 0; j < n; ++j) {
            if (can[i][j]) {
                for (int v : q[j * 100 + c]) {
                    can[i + 1][v] = true;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (t[i] && can[len - 1][i]) {
            cout << "Accepts";
            return 0;
        }
    }
    cout << "Rejects";
    return 0;
}