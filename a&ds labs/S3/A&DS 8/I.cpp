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

constexpr int MAXN = 3 * e5  +1;
constexpr int MAXM = 3 * e5  +1;
constexpr int MAXK = 1;

struct vx {
//    set<int> e{};
    vector<int> re{};
    int cnt = 0;
    int deg = 0;
};

int main() {
//    cout << "1";
    queue<int> q{};
//    cout << "2";
    vector<vx> vxs{};
//    cout << "3";
    int n, m;
//    cout << "4";
    int res[MAXN]{};
    while (cin >> n) {
//        cout << "5";
//        0 = ? 1 = LOSE 2 = WIN
        cin >> m;
//        cout << "6";
        memset(res, 0, sizeof(int) * n + 1);
//        cout << "7";
        vxs.clear();
//        cout << "8";
        for (int i = 0; i <= n; ++i) {
            vxs.pb({});
        }
//        cout << "9";
        for (int i = 0; i < m; ++i) {
            int from, to;
            cin >> from >> to;
            ++vxs[from].deg;
//            vxs[from].e.insert(to);
            vxs[to].re.pb(from);
        }
//        cout << "10";
        for (int i = 1; i <= n; ++i) {
            if (vxs[i].deg == 0) {
                res[i] = 1;
                q.push(i);
            }
        }
//        cout << "11";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (res[v] == 1) {
                for (auto u: vxs[v].re) {
                    if (res[u] == 0) {
                        res[u] = 2;
                        q.push(u);
                    }
                }
            } else if (res[v] == 2) {
                for (auto u: vxs[v].re) {
                    ++vxs[u].cnt;
                    if (vxs[u].cnt == vxs[u].deg) {
                        res[u] = 1;
                        q.push(u);
                    }
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            switch (res[i]) {
                case 0:
                    cout << "DRAW\n";
                    break;
                case 1:
                    cout << "SECOND\n";
                    break;
                case 2:
                    cout << "FIRST\n";
            }
        }
        cout << '\n';
    }
    return 0;
}