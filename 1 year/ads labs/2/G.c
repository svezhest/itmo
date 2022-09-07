#include <stdio.h>
#include <stdlib.h>

#define print(a) printf("%d\n", a);
#define read(a) scanf("%d", &a);

typedef struct Min_Max_Set {
    struct Min_Max_Set* father;
    int size;
    int min;
    int max;
} Sett;


Sett* init(int x) {
    Sett* sett = malloc(sizeof(Sett));
    sett->father = sett;
    sett->size = 1;
    sett->min = x;
    sett->max = x;
    return sett;
}


Sett* find(Sett* sett) {
    if (sett->father != sett) {
        sett->father = find(sett->father);
    }
    return sett->father;
}


void connect(Sett* big, Sett* small) {
    big = find(big);
    small = find(small);
    if (big == small) {
        return;
    }
    if (big->size < small->size) {
        Sett* t = big;
        big = small;
        small = t;
    }
    small->father = big;
    big->size += small->size;
    if (small->max > big->max) {
        big->max = small->max;
    }
    if (small->min < big->min) {
        big->min = small->min;
    }
}


int main() {
    int n;
    read(n)
    Sett* sets[n + 1];
    Sett* temp = NULL;
    for (int i = 1; i <= n; ++i) {
        sets[i] = init(i);
    }
    char c = 0;
    int a, b;
    char buff[256];
    while (c != - 1) {
        do {
            c = getchar();
        } while (c != 'u' && c != 'g' && c != -1);
        if (c == 'u') {
            scanf("%s %d %d", &buff, &a, &b);
            connect(sets[a], sets[b]);
        } else if (c == 'g') {
            scanf("%s %d", &buff, &a);
            temp = find(sets[a]);
            printf("%d %d %d\n", temp->min, temp->max, temp->size);
        }

    }
    return 0;
}