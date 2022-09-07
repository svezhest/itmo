#include <iostream>

using namespace std;

int actualsize = 0;

void siftDown(int *heap, int i) {
    int left = i * 2;
    int right = left + 1;
    if (left < actualsize && heap[i] < heap[left]) {
        if (right < actualsize && heap[left] < heap[right]) {
            swap(heap[right], heap[i]);
            siftDown(heap, right);
        } else {
            swap(heap[left], heap[i]);
            siftDown(heap, left);
        }
    } else if (right < actualsize && heap[i] < heap[right]) {
        swap(heap[right], heap[i]);
        siftDown(heap, right);
    }
}

void siftUp(int *heap, int i) {
    if (i == 1) {
        return;
    }
    if (heap[i] > heap[i / 2]) {
        swap(heap[i], heap[i / 2]);
        siftUp(heap, i / 2);
    }
}

int extract(int *heap) {
    int max = heap[1];
    actualsize--;
    swap(heap[1], heap[actualsize]);
    siftDown(heap, 1);
    return max;
}

void insert(int *heap, int x) {
    heap[actualsize] = x;
    siftUp(heap, actualsize);
    actualsize++;
}

void arrayHeapSort(int *array, int n) {
    int heap[n + 1];
    actualsize = 1;
    for (int i = 0; i < n; ++i) {
        insert(heap, array[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        array[i] = extract(heap);
    }
}

struct Node {
    int valueFrom;
    int valueTo;
    int size;
    Node *left;
    Node *right;
};

void treeGen(Node *node, int *a, int start, int end) {
    node->valueFrom = a[start];
    node->valueTo = a[end - 1];
    node->size = end - start;
    if (start >= end || a[start] == a[end - 1]) {
        node->left = NULL;
        node->right = NULL;
        return;
    }
    node->left = new Node;
    node->right = new Node;
    treeGen(node->left, a, start, start + (end + 1 - start) / 2);
    treeGen(node->right, a, start + (end + 1 - start) / 2, end);
}

int treeSearch(Node *node, int from, int to) { // FROM, TO IS SORTED
    if (node->valueFrom >= from && node->valueTo <= to) {
        return node->size;
    }
    if (node->valueTo < from || node->valueFrom > to) {
        return 0;
    }
    return treeSearch(node->left, from, min(node->valueTo, to)) +
           treeSearch(node->right, max(node->valueFrom, from), to);
}

int maxsize = 0;

void treeFindSize(Node *node, int pos = 1) {
    if (pos > maxsize) {
        maxsize = pos;
    }
    if (node->left != NULL) {
        treeFindSize(node->left, pos * 2);
    }
    if (node->right != NULL) {
        treeFindSize(node->right, pos * 2 + 1);
    }
}

void treeToTable(Node *node, int **table, int pos = 1) {
    table[pos][0] = node->valueFrom;
    table[pos][1] = node->valueTo;
    if (node->left != NULL) {
        treeToTable(node->left, table, pos * 2);
    }
    if (node->right != NULL) {
        treeToTable(node->right, table, pos * 2 + 1);
    }
}

bool checkLog(int x) {
    x += 1;
    while (x % 2 == 0) {
        x /= 2;
    }
    return x == 1 ? true : false;
}

void treePrint(Node *node) {
    maxsize = 0;
    treeFindSize(node);
    maxsize++;
    fflush(stdout);
    int **table = new int *[maxsize];
    for (int i = 0; i < maxsize; ++i) {
        table[i] = new int[2];
        table[i][0] = 1;
        table[i][1] = 0; // NEVER EVER HAPPENS IN SORTED ARRAY
    }
    treeToTable(node, table);
    for (int i = 1; i < maxsize; ++i) {
        if (!(table[i][0] == 1 && table[i][1] == 0)) { // SUCH NODE EXISTS
            cout << table[i][0] << " ~~ " << table[i][1] << "   ";
        }
        if (checkLog(i)) {
            cout << '\n';
        }
    }
    for (int i = 0; i < maxsize; ++i) {
        delete[] table[i];
    }
    delete[] table;
}


int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    arrayHeapSort(a, n);
    Node *tree = new Node;
    treeGen(tree, a, 0, n);
//    treePrint(tree);
    cin >> n;
    while (n--) {
        int a, b;
        cin >> a >> b;
        cout << treeSearch(tree, min(a, b), max(a, b)) << ' ';
    }
    return 0;
}