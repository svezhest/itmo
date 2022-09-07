#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define START_SIZE 16
#define print(int_var) printf("%d\n", int_var);

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


int last(Stack* stack) {
    return stack->content[stack->pos - 1];
}


typedef struct Stack_Min_Type{
    Stack* master;
    Stack* mins;
} StackM;


int getmin(StackM* stackM) {
    if (stackM->mins->pos == 0) {
        return INT_MAX;
    }
    return last(stackM->mins);
}

StackM* initM() {
    StackM* new_stack = NULL;
    new_stack = malloc(sizeof(StackM));
    new_stack->master = init();
    new_stack->mins = init();
    return new_stack;
}


void pushM(StackM* stackM, int x) {
    push(stackM->master, x);
    if (x <= getmin(stackM)) {
        push(stackM->mins, x);
    }
}


int popM(StackM* stackM) {
    if (last(stackM->master) == getmin(stackM)) {
        pop(stackM->mins);
    }
    return pop(stackM->master);
}


int main() {
    StackM* s = initM();
    int n, m, x;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        if (m == 1) {
            scanf("%d", &x);
            pushM(s, x);
        } else if (m == 2) {
            popM(s);
        } else {
            print(getmin(s));
        }
    }
    return 0;
}