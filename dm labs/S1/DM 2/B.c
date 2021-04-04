#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("bwt.in", "r", stdin);
    freopen("bwt.out", "w", stdout);
    int len = 1000;
    char* shifts[1000];
    char c;
    for (int i = 0; i < 1000; ++i) {
        shifts[i] = malloc(sizeof(char) * 1000); // cheat
        c = getchar();
        if (c == -1 || c == '\n') {
            len = i;
            break;
        }
        shifts[0][i] = c;
    }

    for (int i = 1; i < len; ++i) {
        for (int j = 0; j < len; j++) {
            shifts[i][j] = shifts[0][(j + i) % len];
        }
    }

    char* temp;

    for (int pos = len - 1; pos >= 0; --pos) {
        for (int i = 1; i < len; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (shifts[j][pos] > shifts[j + 1][pos]) {
                    temp = shifts[j];
                    shifts[j] = shifts[j + 1];
                    shifts[j + 1] = temp;
                } else {
                    break;
                }
            }
        }
    }

    for (int i = 0; i < len; ++i) {
        putchar(shifts[i][len - 1]);
    }
    return 0;
}