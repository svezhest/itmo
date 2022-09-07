#include <iostream>
#include <algorithm>
#include <map>
#include <queue>

#define long long long

using namespace std;

#define MAXIM_MIKHALYCH 2000

bool t[MAXIM_MIKHALYCH];
int eg[MAXIM_MIKHALYCH][26];
vector<int> reg[MAXIM_MIKHALYCH][26];
bool visited[MAXIM_MIKHALYCH] = {};
bool visited_back[MAXIM_MIKHALYCH] = {};
bool mrk[MAXIM_MIKHALYCH][MAXIM_MIKHALYCH];

void dfs(int u) {
    if (!visited[u]) {
        visited[u] = true;
        for (int c = 0; c < 26; ++c) {
            dfs(eg[u][c]);
        }
    }
}

void dfs_back(int u) {
    if (!visited_back[u]) {
        visited_back[u] = true;
        for (int c = 0; c < 26; ++c) {
            for (int v : reg[u][c]) {
                dfs_back(v);
            }
        }
    }
}

int main() {
//    freopen("minimization.in", "r", stdin);
//    freopen("minimization.out", "w", stdout);
    int n, m, k;
    cin >> n >> m >> k;
    ++n;
    for (int i = 0; i < n; ++i) {
        t[i] = false;
    }
    for (int i = 0; i < k; ++i) {
        int tmp;
        cin >> tmp;
        t[tmp] = true;
    }
    for (int i = 0; i < n; ++i) {
        for (int c = 0; c < 26; ++c) {
            eg[i][c] = 0;
        }
    }
    for (int i = 0; i < m; ++i) {
        int from, to;
        char c;
        cin >> from >> to >> c;
        eg[from][c - 'a'] = to;
    }
    for (int i = 0; i < n; ++i) {
        for (int c = 0; c < 26; ++c) {
            reg[eg[i][c]][c].push_back(i);
        }
    }
    queue<pair<int, int>> queue;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mrk[i][j] = false;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!mrk[i][j] && t[i] != t[j]) {
                mrk[i][j] = mrk[j][i] = true;
                queue.push({i, j});
            }
        }
    }
    while (!queue.empty()) {
        auto p = queue.front();
        queue.pop();
        for (int c = 0; c < 26; ++c) {
            for (int u : reg[p.first][c]) {
                for (int v : reg[p.second][c]) {
                    if (!mrk[u][v]) {
                        mrk[u][v] = mrk[v][u] = true;
                        queue.push({u, v});
                    }
                }
            }
        }
    }
    dfs(1);
    for (int i = 0; i < n; ++i) {
        if (t[i]) {
            dfs_back(i);
        }
    }
    int cmp[MAXIM_MIKHALYCH] = {};
    for (int i = 0; i < n; ++i) {
        if (mrk[0][i]) {
            cmp[i] = -1;
        }
    }
    int cnt = 0;
    for (int i = 1; i < n; ++i) {
        if (!visited[i] || !visited_back[i]) {
            continue;
        }
        if (cmp[i] == -1) {
            ++cnt;
            cmp[i] = cnt;
            for (int j = i + 1; j < n; ++j) {
                if (!mrk[i][j]) {
                    cmp[j] = cnt;
                }
            }
        }
    }
    ++cnt;
    bool nt[MAXIM_MIKHALYCH] = {};
    for (int i = 0; i < n; ++i) {
        nt[cmp[i]] = nt[cmp[i]] || t[i];
    }
    int neg[MAXIM_MIKHALYCH][26];
    for (int i = 0; i < MAXIM_MIKHALYCH; ++i) {
        for (int c = 0; c < 26; ++c) {
            neg[i][c] = 0;
        }
    }
    for(int i = 0; i < n; ++i) {
        for (int c = 0; c < 26; ++c) {
//            cerr << cmp[1] << ' ';
            neg[cmp[i]][c] = cmp[eg[i][c]];
//            cerr << cmp[1] << '\n';
        }
    }
    int mcnt = 0;
    int kcnt = 0;
    for (int i = 1; i < cnt; ++i) {
        if (nt[i]) {
            ++kcnt;
        }
        for (int c = 0; c < 26; ++c) {
            if (neg[i][c] != 0) {
                ++mcnt;
            }
        }
    }
    cout << cnt - 1 << ' ' << mcnt << ' ' << kcnt << '\n';
    for (int i = 0; i < cnt; ++i) {
        if (nt[i]) {
            cout << nt[i] << ' ';
        }
    }
    cout << '\n';
    for (int i = 1; i < cnt; ++i) {
        for (int c = 0; c < 26; ++c) {
            if (neg[i][c] != 0) {
                cout << i << ' ' << neg[i][c] << ' ' << (char)(c + 'a') << '\n';
            }
        }
    }
    return 0;
}