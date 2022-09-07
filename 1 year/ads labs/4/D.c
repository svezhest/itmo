#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int cnt;
    int lx;
    int rx;
    int lng;
    int lclr;
    int rclr;
    struct Node *l;
    struct Node *r;
} Node;

void setWhite(Node *node) {
    node->cnt = 0;
    node->lng = 0;
    node->lclr = 0;
    node->rclr = 0;
}

void setBlack(Node *node) {
    node->cnt = 1;
    node->lng = node->rx - node->lx;
    node->lclr = 1;
    node->rclr = 1;
}

void build(Node *current, int left, int right) {
    current->l = NULL;
    current->r = NULL;
    current->lx = left;
    current->rx = right;
    setWhite(current);
    if (left < right - 1) {
        current->l = malloc(sizeof(Node));
        build(current->l, left, (left + right) / 2);

        current->r = malloc(sizeof(Node));
        build(current->r, (left + right) / 2, right);
    }
}


void propagate(Node *current) {
    if (current->l != NULL) {
        if (current->cnt == 0) {
            setWhite(current->l);
            setWhite(current->r);
        } else if (current->cnt == 1 && current->lclr == 1 && current->rclr == 1) {
            setBlack(current->l);
            setBlack(current->r);
        }
    }
}

void set(int v, Node *current, int l, int r, int lx, int rx) {
    if (l <= lx && rx <= r) {
        if (v == 0) {
            setWhite(current);
        } else {
            setBlack(current);
        }
        return;
    }
    if (l >= rx || lx >= r) {
        return;
    }
    propagate(current);
    set(v, current->l, l, r, lx, (lx + rx) / 2);
    set(v, current->r, l, r, (lx + rx) / 2, rx);
    current->cnt = current->l->cnt + current->r->cnt - current->l->rclr * current->r->lclr;
    current->lng = current->l->lng + current->r->lng;
    current->lclr = current->l->lclr;
    current->rclr = current->r->rclr;
}

void clear(Node *current) {
    if (current->l != NULL) {
        clear(current->l);
    }
    if (current->r != NULL) {
        clear(current->r);
    }
    free(current);
}

int main() {
    Node *tree = malloc(sizeof(Node));
    int sz = 500000;
    build(tree, -sz, sz);
    int n;
    scanf("%d\n", &n);
    for (int i = 0; i < n; ++i) {
        char c;
        int l, r;
        scanf("\n%c %d %d", &c, &l, &r);
        set(c == 'W' ? 0 : 1, tree, l, l + r, -sz, sz);
        printf("%d %d\n", tree->cnt, tree->lng);
    }
    clear(tree);
    return 0;
}