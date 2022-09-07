#include <bits/stdc++.h>

using namespace std;

int n, x, y, z, x2, y2, z2;


void setz(int *a, int v, int zi, int l, int r) {
    a[zi] += v;
    if (zi < 127) {
        int ml = (l + r) / 2;
        int mr = (l + r + 1) / 2;
        if (z <= ml) {
            setz(a, v, 2 * zi + 1, l, ml);
        } else {
            setz(a, v, 2 * zi + 2, mr, r);
        }
    }
}


void sety(int **a, int v, int yi, int l, int r) {
    setz(a[yi], v, 0, 0, n - 1);
    if (yi < 127) {
//        if (!yi) {
//            a[xi][yi][0] += v;
//        }
        int ml = (l + r) / 2;
        int mr = (l + r + 1) / 2;
        if (y <= ml) {
            sety(a, v, 2 * yi + 1, l, ml);
        } else {
            sety(a, v, 2 * yi + 2, mr, r);
        }
    }
}


void setx(int ***a, int v, int xi, int l, int r) {
    sety(a[xi], v, 0, 0, n - 1);
    if (xi < 127) {
//        if (!xi) {
//            a[xi][0][0] += v;
//        }
        int ml = (l + r) / 2;
        int mr = (l + r + 1) / 2;
        if (x <= ml) {
            setx(a, v, 2 * xi + 1, l, ml);
        } else {
            setx(a, v, 2 * xi + 2, mr, r);
        }
    }
}


int findz(int *a, int zi, int l, int r) {
    if (r < z || z2 < l) {
        return 0;
    }
    if (z <= l && r <= z2) {
        return a[zi];
    }
    int ml = (l + r) / 2;
    int mr = (l + r + 1) / 2;
    return findz(a, 2 * zi + 1, l, ml) + findz(a, 2 * zi + 2, mr, r);
}


int findy(int **a, int yi, int l, int r) {
    if (r < y || y2 < l) {
        return 0;
    }
    if (y <= l && r <= y2) {
        return findz(a[yi], 0, 0, n - 1);
    }
    int ml = (l + r) / 2;
    int mr = (l + r + 1) / 2;
    return findy(a, 2 * yi + 1, l, ml) + findy(a, 2 * yi + 2, mr, r);
}

int findx(int ***a, int xi, int l, int r) {
    if (r < x || x2 < l) {
        return 0;
    }
    if (x <= l && r <= x2) {
        return findy(a[xi], 0, 0, n - 1);
    }
    int ml = (l + r) / 2;
    int mr = (l + r + 1) / 2;
    return findx(a, 2 * xi + 1, l, ml) + findx(a, 2 * xi + 2, mr, r);
}

int main() {
    int ***a = new int **[255];
    for (int i = 0; i < 255; ++i) {
        a[i] = new int *[255];
        for (int j = 0; j < 255; ++j) {
            a[i][j] = new int[255];
            for (int k = 0; k < 255; ++k) {
                a[i][j][k] = 0;
            }
        }
    }
    int t, v;
    bool cycle = true;
    cin >> n;
    while (cycle) {
        cin >> t;
        switch (t) {
            case 1:
                cin >> x >> y >> z >> v;
                setx(a, v, 0, 0, n - 1);
                break;
            case 2:
                cin >> x >> y >> z >> x2 >> y2 >> z2;
                cout << findx(a, 0, 0, n - 1) << '\n';
                break;
            default:
                cycle = false;
        }
    }
    for (int i = 0; i < 255; ++i) {
        for (int j = 0; j < 255; ++j) {
            free(a[i][j]);
        }
        free(a[i]);
    }
    free(a);
    return 0;
}