#include <iostream>

using namespace std;
#define ll long long
#define ull unsigned long long
#define F first
#define S second
#define pb push_back

template <typename Int>
struct gcd_ans {
    Int x, y, gcd;
};

template <typename Int>
gcd_ans<Int> gcd(Int a, Int b) {
    if (b == 0) {
        return {1, 0, a};
    }
    auto res = gcd(b, a % b);
    return {res.y, res.x - (a / b) * res.y, res.gcd};
}

template <typename Int>
Int reverse_element(Int x, Int mod) {
    auto res = gcd(x, mod);
    if (res.gcd != 1) {
        throw invalid_argument("No reverse element exists for x = " + to_string(x) + ", mod = " + to_string(mod));
    }
    return (res.x % mod + mod) % mod;
}

int main() {
    ll n, m, a, b;
    cin >> a >> b >> n >> m;
    cout << (a * m * reverse_element(m % n, n) + b * n * reverse_element(n % m, m)) % (n * m);
}