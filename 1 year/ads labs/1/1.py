def mergesort(arr, left, right):
    split = (left + right) // 2

    def merge():
        temp_len = right - left
        temp = [None] * temp_len
        pos_l = left
        pos_r = split
        pos_t = 0
        while pos_t < temp_len:
            if pos_r == right or pos_l != split and arr[pos_l] < arr[pos_r]:
                temp[pos_t] = arr[pos_l]
                pos_t += 1
                pos_l += 1
            else:
                temp[pos_t] = arr[pos_r]
                pos_t += 1
                pos_r += 1
        arr[left:right] = temp
        del temp

    if left < right - 1:
        mergesort(arr, left, split)
        mergesort(arr, split, right)
        merge()


n = int(input())
arr = list(map(int, input().split()))
mergesort(arr, 0, n)
for i in arr:
    print(i, end=' ')
