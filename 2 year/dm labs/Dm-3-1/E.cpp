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
    int n;
    cin >> n;
    vector<set<pair<int, int>>> edges(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int from, to;
        cin >> from >> to;
        edges[from].insert({to, from});
        edges[to].insert({from, to});
    }
    set<pair<int, int>> q;
    for (int i = 1; i <= n; ++i) {
        if (edges[i].size() == 1) {
            q.insert({(*(edges[i].begin())).S, (*(edges[i].begin())).F});
        }
    }
    for (int i = 2; i < n; ++i) {
        auto it = q.begin();
        auto &p = *(q.begin());
        cout << p.S << ' ';
        edges[p.S].erase(edges[p.S].find({p.F, p.S}));
        if (edges[p.S].size() == 1) {
            q.insert({(*(edges[p.S].begin())).S, (*(edges[p.S].begin())).F});
        }
        q.erase(it);
    }
    return 0;
}