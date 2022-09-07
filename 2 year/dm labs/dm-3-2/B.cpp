#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define ull unsigned long long
#define F first
#define S second
#define pb push_back

int cycle_counter = 0;

auto hash_int = hash<int>();
auto hasher = [](const pair<int, int> &p) { return hash_int.operator()(p.second); };

// n
vector<char> visited;
vector<unordered_set<pair<int, int>, decltype(hasher)>> edges;
vector<pair<unordered_map<pair<int, int>, unordered_set<pair<int, int>, decltype(hasher)>,
        decltype(hasher)>, unordered_set<pair<int, int>, decltype(hasher)>>> tree_edges;
vector<pair<int, int>> current_child;

// m
set<pair<int, int>> weights;
vector<set<int>> edge2cycles;

// m or less
unordered_set<int> cycles;

void dfs1(int v) {
    visited[v] = true;
    for (auto &p : edges[v]) {
        if (visited[p.F]) {
            tree_edges[p.F].F[current_child[p.F]].emplace(v, p.S);
            if (v != current_child[p.F].F) {
                tree_edges[v].S.insert(p);
            }
        } else {
            current_child[v] = p;
            dfs1(p.F);
        }
    }
}

void dfs2(int v) {
    for (auto &p : tree_edges[v].S) {
        cycles.erase(*edge2cycles[p.S].begin());
    }
    for (auto[down_edge, up_edges] : tree_edges[v].F) {
        for (auto &p : up_edges) {
            cycles.insert(cycle_counter);
            edge2cycles[p.S].insert(cycle_counter++);
        }
        edge2cycles[down_edge.S].insert(cycles.begin(), cycles.end());
        dfs2(down_edge.F);
        for (auto &p : up_edges) {
            cycles.erase(*edge2cycles[p.S].begin());
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    ull s, cur_s = 0;

    cin >> n >> m >> s;
    ++n;

    visited = vector<char>(n, 0);
    edges = vector<unordered_set<pair<int, int>, decltype(hasher)>>(n);
    tree_edges = vector<pair<unordered_map<pair<int, int>, unordered_set<pair<int, int>, decltype(hasher)>, decltype(hasher)>,
            unordered_set<pair<int, int>, decltype(hasher)>>>(n);
    current_child = vector<pair<int, int>>(n);
    edge2cycles = vector<set<int>>(m);

    vector<pair<int, int>> edge2vs(m);

    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        edge2vs[i] = {a, b};
        edges[a].emplace(b, i);
        edges[b].emplace(a, i);
        weights.emplace(w, i);
    }

    dfs1(1);
    dfs2(1);

//    edges -> cycles
    vector<int> ans;
    vector<char> cycle_used(cycle_counter, 0);
    for (auto[w, edge_num] : weights) {
        if (cur_s + w > s) {
            break;
        }
        for (auto c : edge2cycles[edge_num]) {

            auto[a, b] = edge2vs[edge_num];
            edges[a].erase({b, edge_num});
            edges[b].erase({a, edge_num});
            if (edges[a].size() == 1) {
                int prev = a;
                while (edges[a].size() <= 2) {
                    for (auto[next, bad_edge_num] : edges[a]) {
                        if (next == prev) {
                            continue;
                        }
                        edge2cycles[bad_edge_num].clear();
                        prev = a;
                        a = next;
                    }
                }
            }
            if (edges[b].size() == 1) {
                int prev = b;
                while (edges[b].size() <= 2) {
                    for (auto[next, bad_edge_num] : edges[b]) {
                        if (next == prev) {
                            continue;
                        }
                        edge2cycles[bad_edge_num].clear();
                        prev = b;
                        b = next;
                    }
                }
            }
            ans.pb(edge_num + 1);
            cur_s += w;
            break;
        }
    }
    cout << ans.size() << '\n';
    for (auto x : ans) {
        cout << x << ' ';
    }
    return 0;
}