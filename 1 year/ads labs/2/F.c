#include <stdio.h>
#include <stdlib.h>

#define START_SIZE 16
#define read(a) scanf("%d", &a);

typedef struct Var_Size_Stack {
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
    return stack->content[--(stack->pos)];
}


int last(Stack* stack) {
    return stack->content[stack->pos - 1];
}


int is_empty(Stack* stack) {
    return stack->pos == 0;
}


int compare(int fst, int sec) {
    // what we want
    return fst <= sec;
}


int is_sorted(Stack* stack, int comp(int a, int b)) {
    for (int i = 1; i < stack->pos; ++i) {
        if (!comp(stack->content[i - 1], stack->content[i])) {
            return 0;
        }
    }
    return 1;
}


int main() {
    Stack* stack = init();
    Stack* answer = init();
    Stack* sorted = init();
    int t, n;
    read(n)
    for (int i = 0; i < n; ++i) {
        read(t)
        while (!is_empty(stack) && t > last(stack)) {
            push(sorted, pop(stack));
            push(answer, 'p');
        }

        push(stack, t);
        push(answer, 'a');
    }
    while (!is_empty(stack)) {
        push(sorted, pop(stack));
        push(answer, 'p');
    }

    if (is_sorted(sorted, compare)) {
        for (int i = 0; i < answer->pos; ++i) {
            if (answer->content[i] == 'a') {
                printf("push\n");
            } else if (answer->content[i] == 'p') {
                printf("pop\n");
            }
        }
    } else {
        printf("impossible");
    }
    return 0;
}