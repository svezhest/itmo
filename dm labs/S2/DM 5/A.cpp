#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

bool check(string &word, int pos, int term, vector<pair<string, int>> *v) {
    for (auto &p : v[term]) {
        int j = pos;
        bool comp = true;
        for (int i = 0; i < p.first.size() - (p.second == -1 ? 0 : 1); ++i) {
            if (j == word.size() || word[j] != p.first[i]) {
                comp = false;
                break;
            }
            ++j;
        }
        if (!comp) {
            continue;
        }
        if (j == word.size() ? p.second == -1 : p.second != -1 && check(word, j, p.second, v)) {
            return true;
        }
    }
    return false;
}

int main() {
    freopen("automaton.in", "r", stdin);
    freopen("automaton.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, start;
    char t;
    string arrow;
    string to;
    cin >> n >> t;
    start = t - 'A';
    vector<pair<string, int>> v[26];
    for (int i = 0; i < n; ++i) {
        cin >> t >> arrow >> to;
        v[t - 'A'].emplace_back(to, 'A' <= to.back() && to.back() <= 'Z' ? to.back() - 'A' : -1);
    }
    cin >> m;
    string word;
    for (int i = 0; i < m; ++i) {
        cin >> word;
        cout << (check(word, 0, start, v) ? "yes" : "no") << '\n';
    }
    return 0;
}
