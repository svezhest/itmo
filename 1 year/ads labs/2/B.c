#include <stdio.h>
#include <stdlib.h>

#define START_SIZE 16
#define print(a) printf("%d\n", a);
#define read(a) scanf("%d", &a);

typedef struct Stack_Type {
    int* content;
    size_t size;
    size_t pos;
} Stack;


Stack* init() {
    Stack *new_stack = NULL;
    new_stack = malloc(sizeof(Stack));
    new_stack->content = malloc(START_SIZE * sizeof(int));
    new_stack->size = START_SIZE;
    new_stack->pos = 0;
    return new_stack;
}


int last(Stack* stack) {
    if (stack->pos <= 0) {
        return -1;
    }
    return stack->content[stack->pos - 1];
}


void resize(Stack* stack) {
    stack->size *= 2;
    stack->content = realloc(stack->content, stack->size * sizeof(int));
}


void push(Stack* stack, int x) {
    if (stack->pos >= stack->size) {
        resize(stack);
    }
    stack->content[stack->pos] = x;
    stack->pos++;
}


int pop(Stack* stack) {
    // no asserts
    // no realloc
    return stack->content[--(stack->pos)];
}


void print_stack(Stack* stack) {
    for (int i = 0; i < stack->pos; ++i) {
        printf("%d ", stack->content[i]);
    }
    printf("\n");
}


int main() {
    Stack* balls = init();
    Stack* how_many = init();
    int i, n, x, k = 0;
    read(n)
    for (i = 0; i < n; ++i) {
        read(x)
        check_streak:
        if (balls->pos != 0 && x == last(balls)) {
            push(balls, x);
            push(how_many, last(how_many) + 1);
            continue;
        }
        int in_row = last(how_many);
        if (in_row > 2) {
            for (int j = 0; j < in_row; ++j) {
                pop(balls);
                pop(how_many);
            }
            k += in_row;
            goto check_streak;
        }
        push(balls, x);
        push(how_many, 1);
    }
    int in_row = last(how_many);
    if (in_row > 2) {
        k += in_row;
    }
    print(k)
    return 0;
}