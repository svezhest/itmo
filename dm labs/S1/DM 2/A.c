#include <stdio.h>
#include <stdlib.h>

#define read(integer) scanf("%d", &integer)
#define print(integer) printf("%d ", integer)
#define endl printf("\n")


void swap(size_t* a, size_t* b) {
    size_t t = *a;
    *a = *b;
    *b = t;
}


int partition(int* arr, int l, int r) {
    int p = l;
    int pivot = arr[p];
    l += 1;
    for (int i = l; i <= r; ++i) {
        if (arr[i] <= pivot) {
            swap(&arr[i], &arr[l]);
            ++l;
        }
    }
    swap(&arr[p], &arr[--l]);
    return l;
}


void quicksort(int* arr, int l, int r) {
    if (l < r) {
        int sorted = 1;
        for (int i = l; i < r; ++i) {
            if (arr[i] > arr[i + 1]) {
                sorted = 0;
                break;
            }
        }
        if (sorted) {
            return;
        }
        int split = partition(arr, l, r);
        quicksort(arr, l, split - 1);
        quicksort(arr, split + 1, r);
    }
}


typedef struct BinaryTree {
    struct BinaryTree* left;
    struct BinaryTree* right;
    unsigned long long value;
} Node;


Node* init(unsigned long long x) {
    Node* new_node = malloc(sizeof(Node));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->value = x;
    return new_node;
}


unsigned long long count(Node* node, int depth) {
    if (node->left == node->right) {
        return depth * node->value;
    }
    return count(node->left, depth + 1) + count(node->right, depth + 1);
}


int main() {
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);
    int n;
    read(n);
    int input[n];
    for (int i = 0; i < n; ++i) {
        read(input[i]);
    }
    quicksort(input, 0, n - 1);
    Node* huff[n];
    for (int i = 0; i < n; ++i) {
        huff[i] = init(input[i]);
    }
    for (int i = 1; i < n; ++i) {
        Node* t = init(huff[i - 1]->value + huff[i]->value);
        t->left = huff[i - 1];
        t->right = huff[i];
        huff[i] = t;
        for (int j = i + 1; j < n; ++j) {
            if (huff[j - 1]->value > huff[j]->value) {
                swap(&huff[j - 1], &huff[j]);
            } else {
                break;
            }
        }
    }
    printf("%llu",count(huff[n - 1], 0));
    return 0;
}