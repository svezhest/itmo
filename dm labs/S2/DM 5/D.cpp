#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    freopen("nfc.in", "r", stdin);
    freopen("nfc.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    char t;
    string arrow;
    string to;
    cin >> n >> t;
    int start = t - 'A';
    vector<string> v[26];
    for (int i = 0; i < n; ++i) {
        cin >> t >> arrow >> to;
        v[t - 'A'].push_back(to);
    }
    string w;
    cin >> w;
    int sz = w.size();
    int dp[26][sz][sz];
    for (int i = 0; i < 26; ++i) {
        for (int l = 0; l < sz; ++l) {
            for (int r = 0; r < sz; ++r) {
                dp[i][l][r] = 0;
            }
        }
    }
    for (int l = 0; l < sz; ++l) {
        for (int i = 0; i < 26; ++i) {
            for (auto &out : v[i]) {
                if (out[0] == w[l]) {
                    dp[i][l][l] = 1;
                    break;
                }
            }
        }
    }
    const int MOD = 1000000007;
    for (int distance = 1; distance < sz; ++distance) {
        for (int l = 0; l < sz - distance; ++l) {
            int r = l + distance;
            for (int i = 0; i < 26; ++i) {
                int sum = 0;
                for (auto &out : v[i]) {
                    if (out.size() != 2) {
                        continue;
                    }
                    for (int k = l; k < r; ++k) {
                        sum = ((sum + static_cast<long long>(dp[out[0] - 'A'][l][k]) * dp[out[1] - 'A'][k + 1][r]) % MOD);
                    }
                }
                dp[i][l][r] = sum;
            }
        }
    }
    cout << dp[start][0][sz - 1];
    return 0;
}
