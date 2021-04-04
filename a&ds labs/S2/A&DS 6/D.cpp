#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int get_not_dead(vector<int> &living_parent, vector<bool> &is_alive, int i) {
    if (is_alive[i]) {
        return i;
    } else {
        living_parent[i] = get_not_dead(living_parent, is_alive, living_parent[i]);
        return living_parent[i];
    }
}

int main() {
    vector<vector<int>> ups;
    vector<int> living_parent;
    vector<bool> is_alive;
    vector<int> distance;
    ups.push_back({0});
    distance.push_back(0);
    is_alive.push_back(true);
    living_parent.push_back(0);
    int M, n = 1;
    cin >> M;
    while (M--) {
        char mode;
        cin >> mode;
        switch (mode) {
            case '+': {
                ++n;
                int a;
                cin >> a;
                ups.push_back({a - 1});
                is_alive.push_back(true);
                distance.push_back(distance[a - 1] + 1);
                living_parent.push_back(get_not_dead(living_parent, is_alive, a - 1));
                int d = 1;
                while (ups.back().back() != 0) {
                    ups.back().push_back(ups[ups.back().back()].size() >= d ? ups[ups.back().back()][d - 1]
                                                                            : ups[ups.back().back()].back());
                    ++d;
                }
                break;
            }
            case '-': {
                int a;
                cin >> a;
                is_alive[a - 1] = false;
                break;
            }
            case '?': {
                int a, b;
                cin >> a >> b;
                --a;
                --b;
                if (distance[a] < distance[b]) {
                    swap(a, b);
                }
                int D = distance[a] - distance[b];
                for (int k = ceil(log2(n)); k >= 0; --k) {
                    if (D >= 1 << k) {
                        a = ups[a][k];
                        D -= 1 << k;
                    }
                }
                if (a == b) {
                    cout << get_not_dead(living_parent, is_alive, a) + 1 << '\n';
                    continue;
                }
                for (int k = ceil(log2(n)); k >= 0; --k) {
                    int u, v;
                    u = ups[a].size() > k ? ups[a][k] : ups[a].back();
                    v = ups[b].size() > k ? ups[b][k] : ups[b].back();
                    if (u != v) {
                        a = u;
                        b = v;
                    }
                }
                cout << get_not_dead(living_parent, is_alive, ups[a][0]) + 1 << '\n';
                break;
            }
        }
    }
}