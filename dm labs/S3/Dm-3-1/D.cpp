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
    vector<vector<int>> edges(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            char t;
            cin >> t;
            if (t == '1') {
                edges[i][j] = 1;
            } else {
                edges[j][i] = 1;
            }
        }
    }
    vector<int> h_path{0};
    for (int i = 1; i < n; ++i) {
        auto it = h_path.begin();
        while (it != h_path.end() && edges[*it][i]) {
            ++it;
        }
        h_path.insert(it, i);
    }

    vector<int> h_cycle{};
//    sorry, but why not
    swap(h_cycle, h_path);
//    will be improved
    while (!edges[h_cycle.back()][h_cycle.front()]) {
        h_path.pb(h_cycle.back());
        h_cycle.pop_back();
    }
    auto next = h_path.begin();
    while (!h_path.empty()) {
        auto it = h_cycle.begin();
        do {
            if (it == h_cycle.end()) {
                ++next;
                break;
            } else if (!edges[*it][*next]) {
                break;
            }
            ++it;
        } while (true);
        if (it != h_cycle.end()) {
            h_cycle.insert(it, h_path.begin(), next + 1);
            h_path.erase(h_path.begin(), next + 1);
            next = h_path.begin();
        }
    }
    for (auto x: h_cycle) {
        cout << x + 1 << ' ';
    }
    return 0;
}