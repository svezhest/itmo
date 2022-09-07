#include <iostream>

using namespace std;

int main() {
    int C[101] = {};
    int t;
    while (cin >> t) {
        C[t]++;
    }
    for (int i = 0; i < 101; ++i) {
        while (C[i]--) {
            cout << i << ' ';
        }
    }
    return 0;
}