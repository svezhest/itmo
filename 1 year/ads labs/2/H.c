#include <stdio.h>
#include <stdlib.h>

#define print(a) printf("%d\n", a);
#define read(a) scanf("%d", &a);

typedef struct Tree_Type {
    struct Tree_Type* boss;
    int exp;
} Player;


Player* init() {
    Player *player = malloc(sizeof(Player));
    player->exp = 0;
    player->boss = player;
    return player;
}

Player* find_boss(Player* player) {
    if (player->boss == player) {
        return player;
    }
    return find_boss(player->boss);
}


void connect(Player* a, Player* b) {
    a = find_boss(a);
    b = find_boss(b);
    if (a == b) {
        return;
    }
    Player* boss = init();
    a->boss = boss;
    b->boss = boss;
}


void add_exp(Player* player, int x) {
    find_boss(player)->exp += x;
}


int get_exp(Player* player) {
    if (player->boss == player) {
        return player->exp;
    }
    return player->exp + get_exp(player->boss);
}

int main() {
    int n, m;
    read(n)
    read(m)
    char c;
    int a, b;
    Player* players[n + 1];
    for (int i = 1; i <= n; ++i) {
        players[i] = init();
    }
    for (int i = 0; i < m; ++i) {
        do {
            c = getchar();
        } while (c != 'a' && c != 'j' && c != 'g');
        switch (c) {
            case 'a':
                scanf("dd %d %d", &a, &b);
                add_exp(players[a], b);
                break;
            case 'j':
                scanf("oin %d %d", &a, &b);
                connect(players[a], players[b]);
                break;
            case 'g':
                scanf("et %d", &a);
                print(get_exp(players[a]));
        }
    }
    return 0;
}