#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int find_depth(int f, int d, vector<vector<int>> args_collection) {
    int dmax = d;
    for (int a = 0; a < args_collection[f].size(); ++a) {
        dmax = max(find_depth(args_collection[f][a], d + 1, args_collection), dmax);
    }
    return dmax;
}

int main() {
    int n, nn;
    cin >> n;
    nn = n + 1;
    string elem[nn];
    for (int i = 0; i < nn; ++i) {
        elem[i] = "";
    }
    vector<vector<int>> args_collection(nn, vector<int>());
    vector<int> links;
    for (int i = 1; i < nn; ++i) {
        int s0, x;
        cin >> s0;
        if (s0 == 0) {
            links.push_back(i);
        } else {
            for (int j = 0; j < s0; ++j) {
                cin >> x;
                args_collection[i].push_back(x);
            }
            getline(cin, elem[i]);
            getline(cin, elem[i]);
        }
    }

    cout << find_depth(n, 0, args_collection) << '\n';

    int val[nn];

    int l = links.size();
    for (int sseed = 0; sseed < 1 << l; ++sseed) {
        int seed = sseed;
        for (int i = l - 1; i >= 0; --i) {
            val[links[i]] = seed % 2;
            seed /= 2;
        }

        for (int i = 1; i < nn; ++i) {
            if (elem[i] != "") {
                int ind = 0;
                for (int a = 0; a < args_collection[i].size(); ++a) {
                    ind = ind * 2 + val[args_collection[i][a]];
                }
                ind *= 2;
                val[i] = elem[i][ind] - '0';
            }
        }

        cout << val[n];
    }

    return 0;
}