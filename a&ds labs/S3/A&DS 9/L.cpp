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

char s[100000];
int n;

char get_ch_in_cycle(int cycle, int pos) {
    return s[(pos + cycle) % n];
}

bool comp (int a, int b) {
    return s[a] < s[b];
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin.get(s, 400001, '\n');
    n = cin.gcount();
    int k_th;
    cin >> k_th;
    int n_up2 = 1;
    int pow2 = 0;
    while (n_up2 < n) {
        n_up2 *= 2;
        ++pow2;
    }
    vector<int> pow2_order;
    for (int i = 0; i < n; ++i) {
        pow2_order.pb(i);
    }
    sort(pow2_order.begin(), pow2_order.end(), &comp);
    vector<int> counters(n, 0);
    vector<int> temp(n);
    vector<vector<int>> classes(2, vector<int>(n));
    vector<int> lcp(n, 0);
    {
        int c = 0;
        classes[0][pow2_order[0]] = c;
        for (int j = 1; j < n; ++j) {
            if (s[pow2_order[j - 1]] != s[pow2_order[j]]) {
                ++c;
            }
            classes[0][pow2_order[j]] = c;
        }
    }
//    sort
    for (int i = 0; i < pow2; ++i) {
        bool odd = i % 2;
        int class_count = 1;
        for (int j = 0; j < n - 1; ++j) {
            if (classes[odd][pow2_order[j]] == classes[odd][pow2_order[j + 1]]) {
                ++lcp[j];
            } else {
                ++class_count;
            }
        }
        memset(counters.data(), 0, class_count * sizeof(int));
        for (int j = 0; j < n; ++j) {
            ++counters[classes[odd][(j + (1 << i)) % n]];
        }
        for (int j = 1; j < class_count; ++j) {
            counters[j] += counters[j - 1];
        }
        counters[class_count - 1] = 0;
        for (int j = 0; j < n; ++j) {
            temp[counters[(classes[odd][(j + (1 << i)) % n] + class_count - 1) % class_count]++] = j;
        }
        memset(counters.data(), 0, class_count * sizeof(int));
        for (int j = 0; j < n; ++j) {
            ++counters[classes[odd][temp[j]]];
        }
        for (int j = 1; j < class_count; ++j) {
            counters[j] += counters[j - 1];
        }
        counters[class_count - 1] = 0;
        for (int j = 0; j < n; ++j) {
            pow2_order[counters[(classes[odd][temp[j]] + class_count - 1) % class_count]++] = temp[j];
        }
        {
            int c = 0;
            classes[!odd][pow2_order[0]] = c;
            for (int j = 1; j < n; ++j) {
                if (classes[odd][pow2_order[j - 1]] != classes[odd][pow2_order[j]] ||
                    classes[odd][(pow2_order[j - 1] + (1 << i)) % n] != classes[odd][(pow2_order[j] + (1 << i)) % n]) {
                    ++c;
                }
                classes[!odd][pow2_order[j]] = c;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (classes[pow2 % 2][i] == k_th - 1) {
            for (int j = 0; j < n; ++j) {
                cout << get_ch_in_cycle(i, j);
            }
            return 0;
        }
    }
    cout << "IMPOSSIBLE";
    return 0;
}