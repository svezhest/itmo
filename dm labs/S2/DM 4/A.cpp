#include <iostream>
#include <fstream>

using namespace std;

int main() {
    freopen("problem1.in", "r", stdin);
    freopen("problem1.out", "w", stdout);
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
    int q[n][26];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 26; ++j) {
            q[i][j] = -1;
        }
    }
    for (int i = 0; i < m; ++i) {
        int from, to;
        char c;
        cin >> from >> to >> c;
        q[from - 1][c - 'a'] = to - 1;
    }
    int cur = 0;
    for (int i = 0; i < s.length(); ++i) {
        int tmp = q[cur][s[i] - 'a'];
        if (tmp == -1) {
            cout << "Rejects";
            return 0;
        }
        cur = tmp;
    }
    if (t[cur]) {
        cout << "Accepts";
    } else {
        cout << "Rejects";
    }
    return 0;
}