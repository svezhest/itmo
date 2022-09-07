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
    vector<int> input;
    vector<int> time_to_insert(n + 1, 0);
    for (int i = 1; i <= n - 2; ++i) {
        int t;
        cin >> t;
        input.pb(t);
        time_to_insert[t] = i;
    }
    set<int> q;
    vector<int> used(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (time_to_insert[i] == 0) {
            q.insert(i);
            used[i] = 1;
        }
    }
    for (int i = 0; i < n - 2; ++i) {
        cout << *q.begin() << ' ' << input[i] << '\n';
        q.erase(q.begin());
        if (time_to_insert[input[i]] <= i + 1 && !used[input[i]]) {
            q.insert(input[i]);
            used[input[i]] = 1;
        }
    }
    cout << *q.begin() << ' ' << *(++q.begin());
    return 0;
}