#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define F first
#define S second
#define pb push_back

int main() {
    constexpr int MAXK = 101;
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    int MAXN = n + 1;
//    и здесь тоже крашится причем прикол тупа return 0
    vector<vector<pair<int, int>>> ins;
    for (int i = 0; i <= n; ++i) {
        ins.pb({});
    }
    for (int i = 0; i < m; ++i) {
        int from, to, w;
        cin >> from >> to >> w;
        ins[to].emplace_back(from, w);
    }
//    !!!!!! у меня крашится на этом моменте, если писать MAXN = 10001 что за йухня
    int d[MAXN][MAXK];
    for (auto &i : d) {
//        ну почему мемсет побайтовыыыыйы
        for (int &j : i) {
            j = -1;
        }
//        кстати стильный код
    }
    d[s][0] = 0;
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (auto &p : ins[j]) {
//                p.F -> j
                if (d[p.F][i - 1] != -1) {
                    if (d[j][i] == -1) {
                        d[j][i] = p.S + d[p.F][i - 1];
                    } else {
                        d[j][i] = min(d[j][i], p.S + d[p.F][i - 1]);
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << (d[i][k] == INT_MAX ? -1 : d[i][k]) << '\n';
    }
    return 0;
}