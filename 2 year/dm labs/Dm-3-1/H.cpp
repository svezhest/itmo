#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define ull unsigned long long
#define F first
#define S second
#define pb push_back
#define uint unsigned int

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

ull pow2(int n) {
    ull ans = 1;
    while (n--) {
        ans *= 2;
    }
    return ans;
}

map<pair<ull, int>, vector<ll>> chrom;

ull encode(vector<set<int>> &edges) {
    int n = edges.size();
    ull code = 0;
    int ind = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            code |= (pow2(ind++)) * (edges[i].find(j) != edges[i].end() ? 1 : 0);
        }
    }
    return code;
}

uint edge_to_bit(int a, int b) {
    return (max(a, b) * (max(a, b) - 1)) / 2 + min(a, b);
}

ull contraction(ull code, int n, int a, int b) {
    vector<set<int>> edges(n - 1);
    int predator = min(a, b), prey = max(a, b);
    assert(prey < n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if ((code & (pow2(edge_to_bit(i, j)))) != 0) {
                int from = (i == prey) ? predator : (i > prey ? i - 1 : i),
                        to = (j == prey) ? predator : (j > prey ? j - 1 : j);
                if (from != to) {
                    edges[from].insert(to);
                    edges[to].insert(from);
                }
            }
        }
    }
    return encode(edges);
}

vector<ll> sum(const vector<ll> &a, const vector<ll> &b) {
    if (a.size() < b.size()) {
        return sum(b, a);
    }
    vector<ll> ans(a);
    for (int i = 0; i < b.size(); ++i) {
        ans[i] += b[i];
    }
    return ans;
}

vector<ll> empty_p(int n) {
    vector<ll> ans(n, 0);
    ans.pb(1);
    return ans;
}

// прикол в том, что я вводил руками и если я накосячил
vector<vector<ll>> k = {
        {1},
        {0, 1},
        {0, -1,      1},
        {0, 2,       -3,      1},
        {0, -6,      11,      -6,       1},
        {0, 24,      -50,     35,       -10,    1},
        {0, -120,    274,     -225,     85,     -15,     1},
        {0, 720,     -1764,   1624,     -735,   175,     -21,   1},
        {0, -5040,   13068,   -13132,   6769,   -1960,   322,   -28,   1},
        {0, 40320,   -109584, 118124,   -67284, 22449,   -4536, 546,   -36, 1},
        {0, -362880, 1026576, -1172700, 723680, -269325, 63273, -9450, 870, -45, 1}
};

vector<ll> &full_p(int n) {
    return k[n];
}

vector<ll> &recur(ull code, int n) {
    if (chrom.find({code, n}) != chrom.end()) {
        return chrom[{code, n}];
    }
    if (code == 0) {
//        empty
        chrom[{code, n}] = empty_p(n);
        return chrom[{code, n}];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if ((code & (pow2(edge_to_bit(i, j)))) == 0) {
                // no edge
                chrom[{code, n}] = sum(recur(code | (pow2(edge_to_bit(i, j))), n),
                                       recur(contraction(code, n, i, j), n - 1));
                return chrom[{code, n}];
            }
        }
    }
//    full graph
    chrom[{code, n}] = full_p(n);
    return chrom[{code, n}];
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<set<int>> edges(n);
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        edges[from - 1].insert(to - 1);
        edges[to - 1].insert(from - 1);
    }
    ull code = encode(edges);
    recur(code, n);
    vector<ll> ans = chrom[{code, n}];
    while (ans.back() == 0) {
        ans.pop_back();
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() - 1 << '\n';
    for (auto x : ans) {
        cout << x << ' ';
    }
    return 0;
}