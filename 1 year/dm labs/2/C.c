#include <stdio.h>
#include <stdlib.h>


int main() {
    freopen("mtf.in", "r", stdin);
    freopen("mtf.out", "w", stdout);
    char *buf = malloc(sizeof(char) * 1000);
    gets(buf);
    int ord [26];
    for (int i = 0; i < 26; ++i) {
        ord[i] = 'a' + i;
    }
    for (int i = 0; i < 1000; ++i) {
        if (buf[i] == '\0') {
            break;
        }
        int j = -1;
        while (ord[++j] != buf[i]);
        printf("%d ", j + 1);
        while (j > 0) {
            int t = ord[j - 1];
            ord[j - 1] = ord[j];
            ord[j--] = t;
        }

    }

    return 0;
}