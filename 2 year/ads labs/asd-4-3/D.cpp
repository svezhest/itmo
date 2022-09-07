#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define pb push_back

template<typename Int>
struct gcd_ans {
    Int x, y, gcd;
};

template<typename Int>
gcd_ans<Int> gcd(Int a, Int b) {
    if (b == 0) {
        return {1, 0, a};
    }
    auto res = gcd(b, a % b);
    return {res.y, res.x - (a / b) * res.y, res.gcd};
}

template<typename Int>
Int reverse_element(Int x, Int mod) {
    auto res = gcd(x, mod);
    if (res.gcd != 1) {
        throw invalid_argument("No reverse element exists for x = " + to_string(x) + ", mod = " + to_string(mod));
    }
    return (res.x % mod + mod) % mod;
}

template<typename Int>
vector<Int> factorization(Int n) {
    vector<Int> res;
    auto f = [&](Int x) {
        while (n % x == 0) {
            n /= x;
            res.pb(x);
        }
    };

    f(2);
    f(3);
    f(5);
    f(7);

    for (Int i = 11; n > 1; i += 10) {
        f(i);
        f(i + 2);
        f(i + 6);
        f(i + 8);
    }

    return res;
}

template<typename Int>
Int mul(Int a, Int b, Int mod) {
    if (a == 0 || b == 0) {
        return 0;
    } else if (a == 1) {
        return b;
    } else if (b == 1) {
        return a;
    } else if (b % 2 == 0) {
        Int half = mul(a, b / 2, mod);
        return (half + half) % mod;
    } else {
        Int half = mul(a, b / 2, mod);
        return (a + half + half) % mod;
    }
}

template<typename Int>
Int pow(Int a, Int n, Int mod) {
    return n == 0 ? 1 :
           n == 1 ? a % mod :
           mul(n % 2 == 0 ? 1 : a, pow(mul(a, a, mod), n / 2, mod), mod);
}


int main() {
    ll n, e, c;
    cin >> n >> e >> c;
    auto f = factorization(n);
    ll p = f[0], q = f[1];
    ll d = reverse_element(e, (p - 1) * (q - 1));
    ll m = pow(c, d, n);
    cout << m;
}