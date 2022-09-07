#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define F first
#define S second
#define pb push_back

constexpr int e4 = 10000;
constexpr int e5 = 100000;
constexpr int e6 = 1000000;
constexpr int e7 = 10000000;
constexpr int e8 = 100000000;
constexpr int e9 = 1000000000;
constexpr ll e10 = 10000000000;

constexpr int MAXN = 1;
constexpr int MAXM = 1;
constexpr int MAXK = 1;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    string p_string, t;
    cin >> p_string >> t;
    string s = p_string + '#' + t;
    int n = s.length();
    vector<ll> p(n + 1);
    p[0] = -1;
    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        int k = p[i - 1];
        while (k >= 0) {
            if (s[k] == s[i - 1]) {
                break;
            }
            k = p[k];
        }
        if ((p[i] = k + 1) == p_string.length()) {
            ans.pb(i - 2 * p[i]);
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i << ' ';
    }
    return 0;
}