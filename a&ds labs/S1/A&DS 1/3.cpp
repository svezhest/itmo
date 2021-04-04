#include <iostream>

using namespace std;

unsigned long long inv = 0;

int msort(int **array, unsigned int n, unsigned int m = 1, unsigned int target = 0) {
    unsigned int d, i, j, p1, p2, e1, e2;
    int **temp;
    temp = new int *[n];
    for (i = 0; i < n; i++) {
        temp[i] = array[i];
    }
    if (n <= 1) {
        return 0;
    }
    for (d = 1; d < n; d *= 2) {
        for (i = 0; i + d < n; i += d * 2) {
            p1 = i;
            j = i;
            p2 = i + d;
            e1 = p2;
            e2 = min(n, i + d * 2);
            while (p1 < e1 && p2 < e2) {
                if (array[p2][target] < array[p1][target]) {
                    temp[j++] = array[p2++];
                    inv += (e1 - p1);
                } else {
                    temp[j++] = array[p1++];
                }
            }
            while (p1 < e1) {
                temp[j++] = array[p1++];
            }
            while (p2 < e2) {
                temp[j++] = array[p2++];
            }
        }
        for (i = 0; i < n; i++) {
            array[i] = temp[i];
        }
    }
    delete[] (temp);
    return 1;
}


int main() {
    unsigned int i, j, n, m = 2, tar = 0;
    int **array;
    cin >> n;
    array = new int *[n];
    for (i = 0; i < n; i++) {
        array[i] = new int[m];
        for (j = 0; j < 1; j++) {
            cin >> array[i][j];
            array[i][1] = i;
        }
    }
    msort(array, n, m, tar);
    cout << inv;
    for (i = 0; i < n; i++) {
        delete[] (array[i]);
    }
    delete[] (array);
}