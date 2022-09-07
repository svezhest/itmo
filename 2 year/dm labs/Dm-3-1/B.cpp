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
    deque<int> q;
    vector<vector<int>> edges(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        q.pb(i);
        for (int j = 0; j < i; ++j) {
            char t;
            cin >> t;
            edges[i][j] = edges[j][i] = (t == '1');
        }
    }
    for (int i = 0; i < n * (n - 1); ++i) {
        optional<int> first_pair_with_first;
        optional<int> double_pair;
        for (int j = 1; j < n; ++j) {
            if (edges[q[0]][q[j]] == 1) {
                if (!first_pair_with_first) {
                    first_pair_with_first = j;
                }
                if (j == 1 || (j < n - 1) && edges[q[1]][q[j + 1]] == 1) {
                    double_pair = j;
                    break;
                }
            }
        }
        int t = (double_pair? double_pair : first_pair_with_first).value();
        for (int k = 0; k < t / 2; ++k) {
            swap(q[k + 1], q[t - k]);
        }
        t = q.front();
        q.pop_front();
        q.pb(t);
    }
    for (auto i : q) {
        cout << ++i << ' ';
    }
    return 0;
}