#include <iostream>
#include <algorithm>
#include <map>
#include <queue>

#define long long long

using namespace std;


int main() {
    freopen("equivalence.in", "r", stdin);
    freopen("equivalence.out", "w", stdout);
    int n1, m1, k1;
    cin >> n1 >> m1 >> k1;
    ++n1;
    bool t1[n1];
    int edges1[n1][26];
    for (int i = 0; i < n1; ++i) {
        t1[i] = false;
    }
    for (int i = 0; i < k1; ++i) {
        int tmp;
        cin >> tmp;
        t1[tmp] = true;
    }
    for (int i = 0; i < n1; ++i) {
        for (int c = 0; c < 26; ++c) {
            edges1[i][c] = 0;
        }
    }
    for (int i = 0; i < m1; ++i) {
        int from, to;
        char c;
        cin >> from >> to >> c;
        edges1[from][c - 'a'] = to;
    }
    int n2, m2, k2;
    cin >> n2 >> m2 >> k2;
    ++n2;
    bool t2[n2];
    int edges2[n2][26];
    for (int i = 0; i < n2; ++i) {
        t2[i] = false;
    }
    for (int i = 0; i < k2; ++i) {
        int tmp;
        cin >> tmp;
        t2[tmp] = true;
    }
    for (int i = 0; i < n2; ++i) {
        for (int c = 0; c < 26; ++c) {
            edges2[i][c] = 0;
        }
    }
    for (int i = 0; i < m2; ++i) {
        int from, to;
        char c;
        cin >> from >> to >> c;
        edges2[from][c - 'a'] = to;
    }
    bool visited[n1][n2];
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            visited[i][j] = false;
        }
    }
    queue<pair<int, int>> double_search;
    double_search.push({1, 1});
    while (!double_search.empty()) {
        pair<int, int> p = double_search.front();
        double_search.pop();
        visited[p.first][p.second] = true;
        if (t1[p.first] != t2[p.second]) {
            cout << "NO";
            return 0;
        }
        for (int c = 0; c < 26; ++c) {
            pair<int, int> next = {edges1[p.first][c], edges2[p.second][c]};
            if (!visited[next.first][next.second] && next.first + next.second != 0) {
                double_search.push(next);
            }
        }
    }
    cout << "YES";
    return 0;
}