#include <iostream>
#include <vector>
#include <map>

#define MAX_SIZE 1000

using namespace std;


int main() {
    freopen("cf.in", "r", stdin);
    freopen("cf.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    string t;
    cin >> n >> t;

    int start = t.front() - 'A';

    vector<vector<int>> v[MAX_SIZE];
    bool is_empty_possible[MAX_SIZE] = {};

    getline(cin, t);

    int chain_t = 'z' + 1;

    for (int i = 0; i < n; ++i) {
        getline(cin, t);
        char nt = t[0];
        cerr << t[t.size()];
        t = t.size() > 4 ? t.substr(5) : "";
        switch (t.size()) {
            case 0:
                is_empty_possible[nt - 'A'] = true;
                v[nt - 'A'].push_back({0});
                break;
            case 1:
                v[nt - 'A'].push_back({1, t.front()});
                break;
            default:
                int from = nt;
                for (int j = 0; j < t.size() - 2; ++j) {
                    v[from - 'A'].push_back({2, t[j], chain_t});
                    from = chain_t++;
                }
                v[from - 'A'].push_back({2, t[t.size() - 2], t.back()});

        }
    }
    bool changed = true;
    for (int iter = 0; changed && iter < MAX_SIZE; ++iter) {
        changed = false;
        for (int i = 0; i < MAX_SIZE; ++i) {
            for (auto &rule : v[i]) {
                switch (rule[0]) {
                    case 1:
                        if (is_empty_possible[rule[1] - 'A']) {
                            is_empty_possible[i] = true;
                            changed = true;
                        }
                        break;
                    case 2:
                        if (is_empty_possible[rule[1] - 'A'] && is_empty_possible[rule.back() - 'A']) {
                            is_empty_possible[i] = true;
                            changed = true;
                        }
                }
            }
        }
    }

    string w;
    cin >> w;
    int sz = w.size();
    bool dp[MAX_SIZE][sz][sz];
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int l = 0; l < sz; ++l) {
            for (int r = 0; r < sz; ++r) {
                dp[i][l][r] = false;
            }
        }
    }
    for (int l = 0; l < sz; ++l) {
        for (int i = 0; i < MAX_SIZE; ++i) {
            for (auto &out : v[i]) {
                if (out[0] == 1 && out[1] == w[l]) {
                    dp[i][l][l] = true;
                    break;
                }
            }
        }
        changed = true;
        for (int iter = 0; changed && iter < MAX_SIZE; ++iter) {
            changed = false;
            for (int i = 0; i < MAX_SIZE; ++i) {
                for (auto &rule : v[i]) {
                    if (rule.front() == 2 &&
                        (is_empty_possible[rule[1] - 'A'] && dp[rule.back() - 'A'][l][l] ||
                         is_empty_possible[rule.back() - 'A'] && dp[rule[1] - 'A'][l][l])
                        || rule.front() == 1 && dp[rule.back() - 'A'][l][l]) {
                        dp[i][l][l] = true;
                        changed = true;
                    }
                }
            }
        }
        dp[w[l] - 'A'][l][l] = true;
    }
    for (int distance = 1; distance < sz; ++distance) {
        for (int l = 0; l < sz - distance; ++l) {
            int r = l + distance;
            for (int i = 0; i < MAX_SIZE; ++i) {
                bool sum = false;
                for (auto &out : v[i]) {
                    if (out.front() != 2) {
                        continue;
                    }
                    for (int k = l; k < r; ++k) {
                        sum = sum || dp[out[1] - 'A'][l][k] && dp[out.back() - 'A'][k + 1][r];
                    }
                }
                dp[i][l][r] = sum;
            }
            changed = true;
            for (int iter = 0; changed && iter < MAX_SIZE; ++iter) {
                changed = false;
                for (int i = 0; i < MAX_SIZE; ++i) {
                    for (auto &rule : v[i]) {
                        if (rule.front() == 2 &&
                            (is_empty_possible[rule[1] - 'A'] && dp[rule.back() - 'A'][l][r] ||
                             is_empty_possible[rule.back() - 'A'] && dp[rule[1] - 'A'][l][r])
                            || rule.front() == 1 && dp[rule.back() - 'A'][l][r]) {
                            dp[i][l][r] = true;
                            changed = true;
                        }
                    }
                }
            }
        }
    }
    cout << (dp[start][0][sz - 1] ? "yes" : "no");
    return 0;
}
