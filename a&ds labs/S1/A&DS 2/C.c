#include <stdio.h>
#include <stdlib.h>

#define print(a) printf("%d\n", a);
#define read(a) scanf("%d", &a);
#define QUEUE_SIZE 100000

typedef struct Static_Size_Queue {
    int* content;
    size_t front;
    size_t back;
} Queue;


Queue* init() {
    Queue* new_queue = malloc(sizeof(Queue));
    new_queue->content = malloc(QUEUE_SIZE * sizeof(int));
    new_queue->front = 0;
    new_queue->back = 0;
    return new_queue;
}


void push(Queue* queue, int id, int* q) {
    queue->content[queue->back] = id;
    q[id] = queue->back++;
}


void pop_from_head(Queue* queue) {
    queue->front++;
}


void pop_from_tail(Queue* queue) {
    queue->back--;
}


int before(Queue* queue, int id, int* q) {
    return q[id] - queue->front;
}


int first(Queue* queue) {
    return queue->content[queue->front];
}


int main() {
    int* q = malloc(100001 * sizeof(int));
    Queue* queue = init();
    int n, t, id;
    read(n)
    for (int i = 0; i < n; ++i) {
        read(t)
        switch (t) {
            case 1:
                read(id);
                push(queue, id, q);
                break;
            case 2:
                pop_from_head(queue);
                break;
            case 3:
                pop_from_tail(queue);
                break;
            case 4:
                read(id)
                print(before(queue, id, q))
                break;
            case 5:
                print(first(queue));
        }
    }
    return 0;
}
