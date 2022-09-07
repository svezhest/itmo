#include <iostream>
#include <vector>
#include <complex>
#include <assert.h>

using namespace std;
#define ll long long
#define ull unsigned long long
#define F first
#define S second
#define pb push_back

template<typename Int>
bool get_nth_bit(Int x, size_t n) {
    return x & (1ULL << n);
}

template<typename Int>
Int log2(Int x) {
    if (x == 0) {
        return 0;
    }
    Int res = 0;
    bool not_pow2 = false;
    while (x > 0) {
        not_pow2 = not_pow2 || (x != 1 && x % 2);
        x /= 2;
        ++res;
    }
    return res + not_pow2 - 1;
}

/**
 * simple example: 3 bit number
 * 0 0 0 -> 0 0 0 [meaningless]
 * 0 0 1 -> 1 0 0 (!)
 * 0 1 0 -> 0 1 0 [meaningless]
 * 0 1 1 -> 1 1 0 (!)
 * 1 0 0 -> 0 0 1 [check = false]
 * 1 0 1 -> 1 0 1 [meaningless]
 * 1 1 0 -> 0 1 1 [check = false]
 * 1 1 1 -> 1 1 1 [meaningless]
 * **/
template<typename Int>
bool check_if_right_sided(Int x, size_t bits) {
    for (size_t i = 0; i < bits / 2; ++i) {
        if (get_nth_bit(x, i) == 0 && get_nth_bit(x, bits - 1 - i) == 1) {
            return false;
        }
    }
    return true;
}

template<typename Int>
Int bitwise_reverse(Int x, size_t bits) {
    Int ans = 0;
    for (size_t i = 0; i < bits; ++i) {
        ans += get_nth_bit(x, bits - 1 - i) * (1ULL << i);
    }
    return ans;
}

void fft_in_place(vector<complex<double>> &p, bool backwards) {
    constexpr double pi = 3.1415926535897932384626433832795;
    size_t n = p.size();
    if (n == 1) {
        return;
    }
    size_t k = ::log2(n);
    for (size_t i = 1; i < n; ++i) {
        if (!check_if_right_sided(i, k)) {
            continue;
        }
        size_t i_reversed = bitwise_reverse(i, k);
        if (i_reversed == i) {
            continue;
        }
        swap(p[i], p[i_reversed]);
    }

    for (size_t iter = 1; iter <= k; ++iter) {
        size_t size = 1ULL << iter;
        size_t half_size = size / 2;
        double angle = 2 * pi / size * (backwards ? -1 : 1);
        complex<double> wc(cos(angle), sin(angle));
        vector<complex<double >> w;
        w.emplace_back(1);
        for (int i = 1; i < half_size; ++i) {
            w.pb(w.back() * wc);
        }
        for (size_t i = 0; i < n; i += size) {
            for (size_t j = 0; j < half_size; ++j) {
                complex<double> a = p[i + j], b = p[i + j + half_size] * w[j];
                p[i + j] = a + b;
                p[i + j + half_size] = a - b;
            }
        }
    }

    if (!backwards) {
        return;
    }
    for (size_t i = 0; i < n; ++i) {
        p[i] /= n;
    }
}

int main() {
    vector<complex<double>> a, b;

    size_t n;
    cin >> n;
    for (size_t i = 0; i <= n; ++i) {
        int x;
        cin >> x;
        a.emplace_back(x);
    }


    for (size_t i = 0; i <= n; ++i) {
        int x;
        cin >> x;
        b.emplace_back(x);
    }


    size_t k = ::log2(n + 1) + 1;
    a.resize(1ULL << k);
    b.resize(1ULL << k);



    fft_in_place(a, false);
    fft_in_place(b, false);
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] *= b[i];
    }
    fft_in_place(a, true);

    size_t resulting_size = a.size() - 1;

    auto trunc = [](complex<double> x) {
        return static_cast<int>(x.real() + 0.5);
    };

    while (trunc(a[resulting_size]) == 0) {
        --resulting_size;
    }

    for (int i = 0; i <= resulting_size; ++i) {
        cout << trunc(a[i]) << ' ';
    }
}
