#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    freopen("epsilon.in", "r", stdin);
    freopen("epsilon.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    char t;
    string arrow;
    string to;
    cin >> n >> t;
    vector<pair<string, bool>> v[26]; // bool -> has terminals
    bool is_empty_possible[26] = {};
    for (int i = 0; i < n; ++i) {
        cin >> t >> arrow;
        getline(cin, to);
        if (to.empty()) {
            is_empty_possible[t - 'A'] = true;
        } else {
            v[t - 'A'].emplace_back(to, false);
        }
    }
    bool changed;
    do {
        changed = false;
        for (int i = 0; i < 26; ++i) {
            if (is_empty_possible[i]) {
                continue;
            }
            for (auto &p : v[i]) {
                if (p.second) {
                    continue;
                }
                bool not_empty = false;
                for (auto &ch : p.first) {
                    if ('A' <= ch && ch <= 'Z') {
                        if (!is_empty_possible[ch - 'A']) {
                            not_empty = true;
                            break;
                        }
                    } else if ('a' <= ch && ch <= 'z') {
                        not_empty = true;
                        p.second = true;
                        break;
                    }
                }
                if (not_empty) {
                    continue;
                } else {
                    changed = true;
                    is_empty_possible[i] = true;
                }
            }
        }
    } while (changed);
    for (int i = 0; i < 26; ++i) {
        if (is_empty_possible[i]) {
            cout << static_cast<char>(i + 'A') << ' ';
        }
    }
    return 0;
}
