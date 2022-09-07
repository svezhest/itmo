#include <stdio.h>
#include <stdlib.h>

#define START_SIZE 16
#define print(int_var) printf("%d\n", int_var);

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


void print_stack(Stack* stack) {
    for (int i = 0; i < stack->pos; ++i) {
        printf("%d ", stack->content[i]);
    }
    printf("\n");
}


int main() {
    Stack* stack = init();
    char c = 0;
    while (c != - 1) {
        c = getchar();
        if ('0' <= c && c <= '9') {
            push(stack, c - '0');
        } else if (c == '+') {
            push(stack, pop(stack) + pop(stack));
        } else if (c == '-') {
            int t = pop(stack);
            push(stack, pop(stack) - t);
        } else if (c == '*') {
            push(stack, pop(stack) * pop(stack));
        }
    }
    print(pop(stack))
    return 0;
}