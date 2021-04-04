#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<pair<string, bool>> *g, bool *visited, int v, bool *useful) {
    if (visited[v] || !useful[v]) {
        return;
    }
    visited[v] = true;
    for (auto &p : g[v]) {
        if (p.second) {
            for (auto &ch : p.first) {
                if ('A' <= ch && ch <= 'Z') {
                    dfs(g, visited, ch - 'A', useful);
                }
            }
        }
    }
}

int main() {
    freopen("useless.in", "r", stdin);
    freopen("useless.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    string t;
    cin >> n >> t;

    int start = t.front() - 'A';

    vector<pair<string, bool>> v[26];
    bool reachable[26] = {};
    bool useful[26] = {};
    bool to_check[26] = {};

    to_check[start] = true;
    getline(cin, t);
    for (int i = 0; i < n; ++i) {
        getline(cin, t);
        char nt = t[0];
        cerr << t[t.size()];
        t = t.size() > 4 ? t.substr(5) : "";
        v[nt - 'A'].emplace_back(t, true);
        to_check[nt - 'A'] = true;
        for (auto &ch : t) {
            if ('A' <= ch && ch <= 'Z') {
                to_check[ch - 'A'] = true;
            }
        }
    }
    bool changed;
    do {
        changed = false;
        for (int i = 0; i < 26; ++i) {
            if (!to_check[i] || useful[i]) {
                continue;
            }
            for (auto &p : v[i]) {
                auto s = p.first;
                bool meaningful = true;
                for (auto &ch : s) {
                    if ('A' <= ch && ch <= 'Z' && !useful[ch - 'A']) {
                        meaningful = false;
                        break;
                    }
                }
                if (meaningful) {
                    useful[i] = changed = true;
                }
            }
        }
    } while (changed);
    for (int i = 0; i < 26; ++i) {
        if (!to_check[i] || !useful[i]) {
            continue;
        }
        for (auto &p : v[i]) {
            for (auto &ch : p.first) {
                if ('A' <= ch && ch <= 'Z' && !useful[ch - 'A']) {
                    p.second = false;
                    break;
                }
            }
        }
    }

    dfs(v, reachable, start, useful);
    for (int i = 0; i < 26; ++i) {
        if (to_check[i] && !reachable[i]) {
            cout << static_cast<char>(i + 'A') << ' ';
        }
    }
    return 0;
}
