#include <bits/stdc++.h>

using namespace std;

class Matrix {
public:
    int values[2][2];
    enum special {
        E,
        zero,
        normal
    };

    special mode = normal;

    Matrix *multiply(Matrix *matrix, int mod) {
        if (mode == E) {
            return matrix;
        }
        if (matrix->mode == E) {
            return this;
        }
        auto *res = new Matrix();
        if (mode == zero || matrix->mode == zero) {
            res->mode = zero;
            return res;
        }
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                res->values[i][j] = 0;
                for (int k = 0; k < 2; ++k) {
                    res->values[i][j] += (values[i][k] * matrix->values[k][j]) % mod;
                }
                res->values[i][j] %= mod;
            }
        }
        return res;
    }

    void in(int mod) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                scanf("%d", &values[i][j]);
                values[i][j] %= mod;
            }
        }
    }

    void print() {
        if (mode == zero) {
            printf("0 0\n0 0\n\n");
            return;
        }
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                printf("%d ", values[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
};

Matrix *E = new Matrix();

Matrix *mul(Matrix **a, int l, int r, int i, int lx, int rx, int mod) {
    if (l <= lx && rx <= r) {
        return a[i];
    }
    if (rx < l || lx > r) {
        return E;
    }
    int ml = (lx + rx) / 2;
    int mr = (lx + rx + 1) / 2;
    return mul(a, l, r, 2 * i + 1, lx, ml, mod)->multiply(mul(a, l, r, 2 * i + 2, mr, rx, mod), mod);
}

int main() {
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
    E->mode = Matrix::E;
    int mod, m, n;
    cin >> mod >> n >> m;
    int nn = 1 << static_cast<int>(ceil(log(n) / log(2)));
    Matrix *a[2 * nn - 1];

    for (int i = nn - 1; i < nn + n - 1; ++i) {
        a[i] = new Matrix();
        a[i]->in(mod);

    }

    for (int i = nn + n - 1; i < 2 * nn - 1; ++i) {
        a[i] = new Matrix();
        a[i]->mode = Matrix::zero;
    }

    for (int i = nn - 2; i >= 0; --i) {
        a[i] = a[2 * i + 1]->multiply(a[2 * i + 2], mod);
    }


    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        mul(a, l, r, 0, 0, nn - 1, mod)->print();
    }
}