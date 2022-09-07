#include <bits/stdc++.h>
using namespace std;

int fact (int n);

int main()
{
    freopen("permutations.in", "r", stdin);
    freopen("permutations.out", "w", stdout);
    int i, n, nn, col, t, tt;
    cin >> n;
    n--;
    nn = n + 1;
    int fast_fact[n];
    for (i = 1; i <= nn; i++)
        fast_fact[i] = fact(i);
    bool num[nn];
    for (i = 0; i < fast_fact[nn]; i++)
    {
        memset(num, 0, nn);
        for (col = n; col > 0; col--)
        {
            t = (i/fast_fact[col])%(col+1);
            tt = 0;
            while (num[tt]) tt++;
            for (; t > 0; t--)
            {
                do
                    tt++;
                while (num [tt]);
            }
            num[tt] = 1;
            cout << tt + 1 << ' ';
        }
        tt = 0;
        while (num[tt]) tt++;
        cout << tt + 1 << '\n';
    }
    return 0;
}

int fact (int n)
{
    int f = 1;
    for (; n >= 2; n--)
        f *= n;
    return f;
}