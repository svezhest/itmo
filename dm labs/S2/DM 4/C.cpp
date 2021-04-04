#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <algorithm>

#define long long long

using namespace std;

void useful(int **edges, int u, bool *visited) {
    if (visited[u]) {
        return;
    }
    visited[u] = true;
    for (int i = 0; i < 26; ++i) {
        int v = edges[u][i];
        if (v != -1 && !visited[v]) {
            useful(edges, v, visited);
        }
    }
}

void useful(vector<int> **edges, int u, bool *visited) {
    if (visited[u]) {
        return;
    }
    visited[u] = true;
    for (int i = 0; i < 26; ++i) {
        for (int v : edges[u][i]) {
            if (v != -1 && !visited[v]) {
                useful(edges, v, visited);
            }
        }
    }
}

void dfs(int **edges, bool *visited, int u, vector<int> &ans) {
    visited[u] = true;
    for (int i = 0; i < 26; ++i) {
        int v = edges[u][i];
        if (v != -1 && !visited[v]) {
            dfs(edges, visited, v, ans);
        }
    }
    ans.push_back(u);
}

bool finite(int **edges, bool *visited, int u, set<int> &hist) {
    visited[u] = true;
    for (int i = 0; i < 26; ++i) {
        int v = edges[u][i];
        if (v != -1) {
            if (hist.count(v) != 0) {
                return false;
            }
            hist.insert(v);
            if (!finite(edges, visited, v, hist)) {
                return false;
            }
            hist.erase(v);
        }
    }
    return true;
}

void tsrort(int n, bool *visited, int **&edges, vector<int> &ans) {
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(edges, visited, i, ans);
        }
    }
//    ans.reverse();
}

int main() {
    freopen("problem3.in", "r", stdin);
    freopen("problem3.out", "w", stdout);
    int n, m, k;
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
    int **q = new int *[n];
//    этот пипец пришлось использовать, чтобы передавать массив в функцию. тупые плюсы.
    vector<int> **revq = new vector<int> *[n];
    for (int i = 0; i < n; ++i) {
        q[i] = new int[26];
        revq[i] = new vector<int>[26];
        for (int j = 0; j < 26; ++j) {
            q[i][j] = -1;
            revq[i][j] = vector<int>();
        }
    }
    for (int i = 0; i < m; ++i) {
        int from, to;
        char c;
        cin >> from >> to >> c;
        q[from - 1][c - 'a'] = to - 1;
        revq[to - 1][c - 'a'].push_back(from - 1);
    }
    bool visited[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }
    for (int i = 0; i < n; ++i) {
        if (t[i]) {
            useful(revq, i, visited);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            for (int j = 0; j < 26; ++j) {
                for (int v : revq[i][j]) {
                    q[v][j] = -1;
                }
                revq[i][j].clear();
//                достаточно того, что мы не сможем туда попасть, но нужен костыль...
            }
            t[i] = false;
        }
    }
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }
//    for (int i = 0; i < n; ++i) {
//        for (int c = 0; c < 26; ++c) {
//            if (q[i][c] != -1) {
//                cout << i + 1 << ' ' << q[i][c] + 1 << ' ' << (char) (c + 'a') << '\n';
//            }
//        }
//    }
//    cout << '\n';
    useful(q, 0, visited);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            for (int j = 0; j < 26; ++j) {
                for (int v : revq[i][j]) {
                    q[v][j] = -1;
                }
                revq[i][j].clear();
//                достаточно того, что мы не сможем туда попасть, но нужен костыль...
            }
            t[i] = false;
        }
    }
//    на данном этапе в "хорошие" вершины будут вести ребра из бесполезых бершин ...
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }
//    for (int i = 0; i < n; ++i) {
//        for (int c = 0; c < 26; ++c) {
//            if (q[i][c] != -1) {
//                cout << i + 1 << ' ' << q[i][c] + 1 << ' ' << (char) (c + 'a') << '\n';
//            }
//        }
//    }
//    cout << '\n';
    set<int> hist;
    if (!finite(q, visited, 0, hist)) {
        cout << -1;
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }
    vector<int> topol;
    tsrort(n, visited, q, topol);
    reverse(topol.begin(), topol.end());
//    for (auto it = topol.begin(); it != topol.end(); ++it) {
//        for (int c = 0; c < 26; ++c) {
//            if (q[*it][c] != -1) {
//                cout << *it + 1 << ' ' << q[*it][c] + 1 << ' ' << (char) (c + 'a') << '\n';
//            }
//        }
//    }
//    cout << '\n';
    long paths[n];
    for (int i = 1; i < n; ++i) {
        paths[i] = 0;
    }
    paths[0] = 1;
    for (int i = 1; i < n; ++i) {
        for (int c = 0; c < 26; ++c) {
            for (int v : revq[topol[i]][c]) {
//                ... вследствие чего есть необходимость выполнять проверку
                if (v != -1 && q[v][c] != -1) {
                    paths[topol[i]] += paths[v];
                }
            }
        }
    }
    long res = 0;
    for (int i = 0; i < n; ++i) {
        if (t[i]) {
            res += paths[i];
        }
    }
    cout << res % 1000000007;
    return 0;
}