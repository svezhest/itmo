#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define F first
#define S second
#define pb push_back

constexpr int MAXN = 100;
constexpr int MAXM = 1;

int main() {
    int n, m;
    float weights[MAXN][MAXN];
    float min_weights[MAXN][MAXN];
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> weights[i][j];
            min_weights[i][j] = weights[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < n; ++l) {
                    min_weights[j][k] = min(min_weights[j][k], min_weights[j][l] + min_weights[l][k]);
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << min_weights[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}