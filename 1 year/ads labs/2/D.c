#include <stdio.h>
#include <stdlib.h>

#define print(a) printf("%d\n", a);
#define read(a) scanf("%d", &a);

typedef struct Linked_Goblin {
    int content;
    struct Linked_Goblin* next;
} Goblin;


Goblin* init(int x) {
    Goblin* new_goblin = malloc(sizeof(Goblin));
    new_goblin->content = x;
    new_goblin->next = NULL;
    return new_goblin;
}


Goblin* append(Goblin* old, Goblin* new) {
    old->next = new;
    return new;
}


void insert_after(Goblin* goblin, Goblin* lucky_goblin) {
    Goblin* unlucky_goblin = goblin->next;
    goblin->next = lucky_goblin;
    lucky_goblin->next = unlucky_goblin;
}


Goblin* pop_from_head(Goblin* head) {
//    free(head);
    return head->next;
}


int main() {
    Goblin* head = NULL;
    Goblin* last = NULL;
    Goblin* mid = NULL;
    Goblin* this = NULL;
    int n, id, size = 0;
    char mode;
    read(n)
    for (int i = 0; i < n; ++i) {
        do {
            scanf("%c", &mode);
        } while (mode != '+' && mode != '*' && mode != '-');

        switch (mode) {
            case '+':
                size++;
                read(id)
                this = init(id);
                if (size == 1) {
                    last = this;
                    head = this;
                    mid = this;
                } else {
                    last = append(last, this);
                    if (size % 2 == 1) {
                        mid = mid->next;
                    }
                }
                break;
            case '*':
                size++;
                read(id)
                this = init(id);
                if (size == 1) {
                    last = this;
                    head = this;
                    mid = this;
                } else {
                    insert_after(mid, this);
                    if (mid == last) {
                        last = this;
                    }
                    if (size % 2 == 1) {
                        mid = mid->next;
                    }
                }
                break;
            case '-':
                size--;
                print(head->content)
                head = pop_from_head(head);
                if (size % 2 == 1) {
                    mid = mid->next;
                }
                break;
        }
    }
    return 0;
}