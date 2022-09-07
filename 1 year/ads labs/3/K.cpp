#include <iostream>
#include <vector>
#include <fstream>
#define range(i, n) for (long long i = 0; i < (n); i++)
using namespace std;

int main() {
    freopen("skyscraper.in", "r", stdin);
    freopen("skyscraper.out", "w", stdout);
    int n;
    long long w;
    int moves = 0;
    cin >> n >> w;
    int c[n];
    vector<int> ln(n);
    vector<vector<int>> gr(n);
    range(i, n) {
        cin >> c[i];
        ln[i] = i;
    }
    long long sz;
    long long maxi;
    long long maxx = 0;
    while (n != 0) {
        sz = 1 << n;
        for(long long i = 1; i < sz; i++) {
            long long t = i;
            long long sm = 0;
            for (int j = 0; j < n; j++, t /= 2) {
                if (t % 2) {
                    sm += c[ln[j]];
                }
            }
            if (sm <= w && sm > maxx) {
                maxx = sm;
                maxi = i;
            }
        }
        int x = 0;
        for (int j = 0; j < n; maxi /= 2) {
            if (maxi % 2) {
                gr[moves].push_back(ln[j] + 1);
                ln.erase(ln.begin() + j);
                vector<int>(ln).swap(ln);
                x++;
            } else {
                j++;
            }
        }
        gr[moves].push_back(x);
        moves++;
        maxx = 0;
        n -= x;
    }
    cout << moves << '\n';
    range(i, moves) {
        cout << gr[i][gr[i].size() - 1];
        range(j, gr[i].size() - 1) {
            cout << ' ' << gr[i][j];
        }
        cout << '\n';
    }
    return 0;
}