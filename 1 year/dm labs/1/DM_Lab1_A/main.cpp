#include <iostream>
#include <set>
#include <vector>

using namespace std;

int n, m, c;
vector<int> ord;

void dfs(bool* used, set<int>* ver, int v) {
    used[v] = true;
    for (auto it = ver[v].begin(); it != ver[v].end(); ++it) {
        if (!used[*it]) {
            dfs(used, ver, *it);
        }
    }
    ord.push_back(v);
}

void revdfs(bool* used, int* comp, set<int>* ver, int v) {
    used[v] = true;
    comp[v] = c;
    for (auto it = ver[v].begin(); it != ver[v].end(); ++it) {
        if (!used[*it]) {
            revdfs(used, comp, ver, *it);
        }
    }
}

inline int compr(int a) {
    if (a < 0) {
        return n - a - 1;
    } else {
        return a - 1;
    }
}

inline int neg(int a) {
    if (a >= n) {
        return a - n;
    } else {
        return a + n;
    }
}

int main() {
    cin >> n >> m;
    set<int> ver[2 * n];
    set<int> revver[2 * n];
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a = compr(a);
        b = compr(b);
        ver[neg(a)].insert(b);
        ver[neg(b)].insert(a);
        revver[b].insert(neg(a));
        revver[a].insert(neg(b));
    }
    bool* used = new bool[2 * n];
    for (int i = 0; i < 2 * n; ++i) {
        used[i] = false;
    }
    int* comp = new int[2 * n];
    for (int i = 0; i < 2 * n; ++i) {
        if (!used[i]) {
            dfs(used, ver, i);
        }
    }
    for (int i = 0; i < 2 * n; ++i) {
        used[i] = false;
    }
    c = 0;
//    for (auto it =ord.begin(); it != ord.end(); ++it) {
//        cout << *it << ' ';
//    }
//    cout << '\n';
    for (int i = 2 * n - 1; i >= 0; --i) {
        if (!used[ord[i]]) {
            revdfs(used, comp, revver, ord[i]);
            c += 1;
        }
    }
//    for (int i = 0; i < 2 * n; ++i) {
//        cout << i << ": ";
//        for (auto it = revver[i].begin(); it != revver[i].end(); ++it) {
//            cout << *it << ' ';
//        }
//        cout <<"*"<<comp[i];
//        cout << '\n';
//    }
    bool ok = true;
    for (int i = 0; i < n; ++i) {
        if (comp[i] == comp[i + n]) {
            ok = false;
            break;
        }
    }
    if (ok) {
        cout << "NO";
    } else {
        cout << "YES";
    }
    return 0;
}