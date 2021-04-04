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
};

void back_dfs(int state, vector<char> &visited, set<int> &ans, vector<Node> &trie) {
    if ((state < 0 || visited[state]) || ((visited[state] = true) && !trie[state].is_term)) {
        return;
    }
    ans.insert(trie[state].input_ind.begin(), trie[state].input_ind.end());
    back_dfs(trie[state].suf, visited, ans, trie);
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
    set<int> term_states{};
    for (auto ch : base) {
        if (pref == -1) {
            pref = 0;
        }
        if (trie[pref].is_term) {
            term_states.insert(pref);
        }
        do {
            auto it = trie[pref].next.find(ch);
            if (it != trie[pref].next.end()) {
                pref = (*it).S;
                break;
            }
            pref = trie[pref].suf;
        } while (pref != -1);
    }
    set<int> ans{};
    vector<char> visited(trie.size(), false);
    for (auto s : term_states) {
        back_dfs(s, visited, ans, trie);
    }
    for (int i = 1; i <= n; ++i) {
        cout << (ans.find(i) != ans.end() ? "YES" : "NO") << '\n';
    }
    return 0;
}