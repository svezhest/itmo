#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    int parents[n + 1];
    parents[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> parents[i];
    }
    vector<int> ups[n + 1];
    int d = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i <= n; ++i) {
            if (ups[i].empty()) {
                if (i != 0) {
                    flag = true;
                }
                ups[i].push_back(parents[i]);
            } else {
                if (!(i == 0 || ups[i].back() == 0)) {
                    flag = true;
                }
                ups[i].push_back(ups[ups[i].back()][d - 1]);
            }
        }
        ++d;
    }
    for (int i = 1; i <= n; ++i) {
        cout << i << ":";
        for (int j = 0; j < ups[i].size(); ++j) {
            if (ups[i][j] == 0) {
                break;
            }
            cout << " " << ups[i][j];
        }
        cout << "\n";
    }
    return 0;
}#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    int parents[n + 1];
    parents[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> parents[i];
    }
    vector<int> ups[n + 1];
    int d = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i <= n; ++i) {
            if (ups[i].empty()) {
                if (i != 0) {
                    flag = true;
                }
                ups[i].push_back(parents[i]);
            } else {
                if (!(i == 0 || ups[i].back() == 0)) {
                    flag = true;
                }
                ups[i].push_back(ups[ups[i].back()][d - 1]);
            }
        }
        ++d;
    }
    for (int i = 1; i <= n; ++i) {
        cout << i << ":";
        for (int j = 0; j < ups[i].size(); ++j) {
            if (ups[i][j] == 0) {
                break;
            }
            cout << " " << ups[i][j];
        }
        cout << "\n";
    }
    return 0;
}