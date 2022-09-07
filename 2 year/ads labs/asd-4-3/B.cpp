#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define ull unsigned long long
#define F first
#define S second
#define pb push_back

auto rng = mt19937(random_device()());

ll mul(ll a, ll b, ll mod) {
    return a == 0 ? 0 :
           b == 0 ? 0 :
           a == 1 ? b :
           b == 1 ? a :
           ((2 * mul(a, b / 2, mod)) % mod + (b % 2) * (a % mod)) % mod;
}

ll pow(ll a, ll n, ll mod) {
    return n == 0 ? 1 :
           n == 1 ? a % mod :
           mul(n % 2 == 0 ? 1 : a, pow(mul(a, a, mod), (n - 1) / 2, mod), mod);
}

bool can_be_prime(ll x) {
    if (x == 1) {
        return false;
    }
    auto dist = uniform_int_distribution<ll>(1, x - 1);
    ll r = dist(rng);
    if (gcd(x, r) != 1) {
        return false;
    }
    ll n = x - 1;
    int i = 0;
    while (n != 0 && n % 2 == 0) {
        n /= 2;
        ++i;
    }
    ll p = pow(r, n, x);
    if (p == 1) {
        return true;
    }
    for (int j = 0; j < i; ++j) {
        ll t = p;
        p = mul(p, p, x);
        if (p == 1) {
            return t == x - 1;
        }
    }
    return false;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        bool prime = true;
        for (int j = 0; j < 50; ++j) {
            if (!can_be_prime(x)) {
                prime = false;
                break;
            }
        }
        cout << (prime ? "YES" : "NO") << '\n';
    }
    return 0;
}