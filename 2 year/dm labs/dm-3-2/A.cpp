#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define ull unsigned long long
#define F first
#define S second
#define pb push_back

int main() {
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    set<pair<int, int>, greater<>> in;
    set<int, greater<>> free{};
    ll s = 0;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        s += b;
        in.emplace(b, a);
        free.insert(i + 1);
    }
    for (auto &p : in) {
        auto it = free.lower_bound(p.S);
        if (it == free.end()) {
            continue;
        }
        s -= p.F;
        free.erase(it);
    }
    cout << s;
    return 0;
}