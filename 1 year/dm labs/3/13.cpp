#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("num2perm.in", "r", stdin);
    freopen("num2perm.out", "w", stdout);
    long long i, n, nn, col, t, tt;
    cin >> n >> i;
    n--;
    nn = n + 1;
    long long fast_fact[nn + 1];
    fast_fact[0] = 1;
    for (i = 1; i <= nn; i++)
        fast_fact[i] = i * fast_fact[i -1];
    bool num[nn];
    memset(num, 0, nn);
    for (col = n; col > 0; col--)
    {
        t = (i/fast_fact[col])%(col+1);
        tt = 0;
        while (num[tt]) tt++;
        while (t--)
            while (num[++tt]);
        num[tt] = 1;
        cout << tt + 1 << ' ';
    }
    tt = 0;
    while (num[tt]) tt++;
    cout << tt + 1 << '\n';
    return 0;
}
