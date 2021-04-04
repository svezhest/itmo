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

string s;

bool comp (int a, int b) {
    return s[a] < s[b];
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> s;
    s.append("$");
    int n = s.length();
    int n_up2 = 1;
    int pow2 = 0;
    while (n_up2 < n) {
        n_up2 *= 2;
        ++pow2;
    }
    vector<int> pow2_order;
    for (int i = 0; i < n; ++i) {
        pow2_order.pb(i);
    }
    sort(pow2_order.begin(), pow2_order.end(), &comp);
    vector<vector<int>> buckets(n);
    vector<vector<int>> buckets2(n);
    vector<vector<int>> classes(pow2, vector<int>(n));
    vector<int> lcp(n, 0);
    {
        int c = 0;
        classes[0][pow2_order[0]] = c;
        for (int j = 1; j < n; ++j) {
            if (s[pow2_order[j - 1]] != s[pow2_order[j]]) {
                ++c;
            }
            classes[0][pow2_order[j]] = c;
        }
    }
//    sort
    for (int i = 0; i < pow2; ++i) {
        bool not_done_yet = false;
        for (int j = 0; j < n - 1; ++j) {
            if (classes[i][pow2_order[j]] == classes[i][pow2_order[j + 1]]) {
                if (lcp[j] == 0) {
                    lcp[j] = 1;
                } else {
                    lcp[j] *= 2;
                }
                not_done_yet = true;
            }
        }
        if (!not_done_yet) {
            break;
        }
        pow2_order.clear();
        for (int j = 0; j < n; ++j) {
            buckets[classes[i][(j + (1 << i)) % n]].pb(j);
        }
        for (auto &v : buckets) {
            for (auto x : v) {
                buckets2[classes[i][x]].pb(x);
            }
        }
        for (auto &v : buckets2) {
            for (auto x : v) {
                pow2_order.pb(x);
            }
        }
        if (i == pow2 - 1) {
            break;
        }
        for (int j = 0; j < n; ++j) {
            buckets[j].clear();
            buckets2[j].clear();
        }
        {
            int c = 0;
            classes[i + 1][pow2_order[0]] = c;
            for (int j = 1; j < n; ++j) {
                if (classes[i][pow2_order[j - 1]] != classes[i][pow2_order[j]] ||
                    classes[i][(pow2_order[j - 1] + (1 << i)) % n] != classes[i][(pow2_order[j] + (1 << i)) % n]) {
                    ++c;
                }
                classes[i + 1][pow2_order[j]] = c;
            }
        }
    }
    for (int i = 1; i < n; ++i) {
        cout << pow2_order[i] + 1 << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n - 1; ++i) {
        int pow2_for_lcp = -1;
        for (int j = lcp[i]; j > 0; j /= 2) {
            ++pow2_for_lcp;
        }
        for (int j = lcp[i]; j > 0; j /= 2, --pow2_for_lcp) {
            if (classes[pow2_for_lcp][(pow2_order[i] + lcp[i]) % n] ==
                classes[pow2_for_lcp][(pow2_order[i + 1] + lcp[i]) % n]) {
                lcp[i] += j;
            }
        }
    }
    for (int i = 1; i < n - 1; ++i) {
        cout << lcp[i] << ' ';
    }
    return 0;
}