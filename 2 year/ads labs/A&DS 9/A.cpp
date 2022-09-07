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
    int m;
    string s;
    cin >> s >> m;
    int n = s.length();
    vector<pair<ll, ll>> h(n + 1);
    h[0] = {0, 1};
    int i = 1;
    for (auto c : s) {
        h[i] = {h[i - 1].F * 31 + (c - 'a' + 1), h[i - 1].S * 31};
        ++i;
    }
    while (m--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << (h[b].F - h[a - 1].F * h[b - a + 1].S ==
                 h[d].F - h[c - 1].F * h[d - c + 1].S ?
                 "Yes" : "No") << '\n';
    }
    return 0;
}