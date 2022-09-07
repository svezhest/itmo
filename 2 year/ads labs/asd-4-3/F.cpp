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

typedef complex<double> base;

int rev (int num, int lg_n) {
    int res = 0;
    for (int i=0; i<lg_n; ++i)
        if (num & (1<<i))
            res |= 1<<(lg_n-1-i);
    return res;
}

const int PI = 3.1415926535897932384626433832795;

void fft (vector<base> & a, bool invert) {
    int n = (int) a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n)  ++lg_n;

    for (int i=0; i<n; ++i)
        if (i < rev(i,lg_n))
            swap (a[i], a[rev(i,lg_n)]);

    for (int len=2; len<=n; len<<=1) {
        double ang = 2*PI/len * (invert ? -1 : 1);
        base wlen (cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            base w (1);
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j],  v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (int i=0; i<n; ++i)
            a[i] /= n;
}

void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {
    vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    size_t n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);

    fft (fa, false),  fft (fb, false);
    for (size_t i=0; i<n; ++i)
        fa[i] *= fb[i];
    fft (fa, true);

    res.resize (n);
    for (size_t i=0; i<n; ++i)
        res[i] = int (fa[i].real() + 0.5);
}

int main() {
    vector<int> a, b;

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

    vector<int> r;
    multiply(a, b, r);
    for (int j = 0; j < 2 * n + 1; ++j) {
        cout << r[j] << ' ';

    }
}
