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

int main() {
    int n;
    cin >> n;

    int heap[n + 1];
    actualsize = 1;
    while (n--) {
        int mode;
        cin >> mode;
        if (mode == 0) {
            int x;
            cin >> x;
            insert(heap, x);
        } else {
            cout << extract(heap) << '\n';
        }
    }
    return 0;
}
