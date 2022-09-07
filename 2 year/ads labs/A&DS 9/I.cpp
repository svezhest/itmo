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

struct Node {
    map<char, int> next{};
    int suf = -1;
    vector<int> input_ind{};
    bool is_term = false;
    int depth = -1;
};

void back_dfs(int state, int first, int last, vector<pair<optional<int>, int>> &ans, vector<Node> &trie) {
if (state < 0 || !trie[state].is_term) {
return;
}
for  (auto i : trie[state].input_ind) {
if (!ans[i].F) {
ans[i].F = first - trie[state].depth;
} else {
ans[i].F = min(ans[i].F.value(), first - trie[state].depth);
}
ans[i].S = max(ans[i].S, last - trie[state].depth);
}
back_dfs(trie[state].suf, first, last, ans, trie);
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<Node> trie(1);
    for (int i = 1; i <= n; ++i) {
        string t;
        cin >> t;
        int state = 0;
        for (auto ch : t) {
            int prev = state;
            auto it = trie[state].next.find(ch);
            if (it != trie[state].next.end()) {
                state = (*it).S;
            } else {
                state = trie[state].next[ch] = trie.size();
                trie.emplace_back();
                trie[state].depth = trie[prev].depth + 1;
            }
        }
        trie[state].input_ind.pb(i);
        trie[state].is_term = true;
    }
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (auto &p : trie[t].next) {
            q.push(p.S);
            char ch = p.F;
            int par = trie[t].suf;
            while (par != -1) {
                if (trie[par].next.find(ch) != trie[par].next.end()) {
                    trie[p.S].suf = trie[par].next[ch];
                    break;
                }
                par = trie[par].suf;
            }
            if (par == -1) {
                trie[p.S].suf = 0;
            }
            trie[p.S].is_term |= trie[trie[p.S].suf].is_term;
        }
    }
    string base;
    cin >> base;
    base.append("$");
    int pref = 0;
    vector<pair<optional<int>, int>> term_states(trie.size(), {optional<int>(), -1});
    int pos = -1;
    for (auto ch : base) {
        if (pref == -1) {
            pref = 0;
        }
        if (trie[pref].is_term) {
            if (!term_states[pref].F) {
                term_states[pref].F = pos;
            } else {
                term_states[pref].F = min(term_states[pref].F.value(), pos);
            }
            term_states[pref].S = max(term_states[pref].S, pos);
        }
        do {
            auto it = trie[pref].next.find(ch);
            if (it != trie[pref].next.end()) {
                pref = (*it).S;
                break;
            }
            pref = trie[pref].suf;
        } while (pref != -1);
        ++pos;
    }
    vector<pair<optional<int>, int>> ans(n + 1, {optional<int>(), -1});
    for (int s = 1; s != trie.size(); ++s) {
        if (term_states[s].F) {
            back_dfs(s, term_states[s].F.value(), term_states[s].S, ans, trie);
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << (ans[i].F ? ans[i].F.value() : -1) << ' ' << ans[i].S << '\n';
    }
    return 0;
}