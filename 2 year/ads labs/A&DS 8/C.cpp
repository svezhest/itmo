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

constexpr int MAXN = 100;
constexpr int MAXM = 1;

int matr[MAXN][MAXN];
ll summ[MAXN] = {};

int n;
bool marked[MAXN] = {};
bool marked_p[MAXN] = {};
vector<int> ans = {};
ll csum;

bool dfs(int v) {
    ans.pb(v);
    if (marked[v]) {
        if (summ[v] > csum) {
            if (marked_p[v]) {
                return true;
            }
        } else {
            ans.pop_back();
            return false;
        }
    }
    marked_p[v] = true;
    summ[v] = csum;
    marked[v] = true;

    for (int i = 0; i < n; ++i) {
        if (i != v && matr[v][i] != e5) {
            csum += matr[v][i];
            if (dfs(i)) {
                return true;
            }
            csum -= matr[v][i];
        }
    }
    marked_p[v] = false;
    ans.pop_back();
    return false;
}

int main() {
    int m;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matr[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        if (matr[i][i] < 0) {
            cout << "YES\n1\n" << i + 1;
            return 0;
        }
        if (marked[i]) {
            continue;
        }
        csum = 0;
        memset(marked_p, 0, MAXN);
        if (dfs(i)) {
            cout << "YES\n";
            vector<int> yes{};
//            cerr << ans.size() << '\n';
//            for ( auto sds : ans) {
//  cerr << sds << ' ';
//}
            int s = ans.back();
            do {
              ans.pop_back();
              if (ans.empty()) {
                  while (true);
//                  this crazyness worked out therefore it will be here forever commented but never forgotten
//                  or no it could be misleading - it wasn't
//                  tl => this stupid shit
//                  rt => other
              }
              yes.pb(ans.back());
            } while(ans.back()!= s);
            cout << yes.size() << '\n';
            for (int j = yes.size() - 1; j >= 0; --j) {
                cout << yes[j] + 1 << ' ';
            }
            return 0;
        }
    }
    cout << "NO";
    return 0;
}