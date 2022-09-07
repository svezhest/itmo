def ask(a, b):
    print(1, a, b, flush=True)
    return input() == "YES"

def mergesort(arr, left, right):
    split = (left + right) // 2

    def merge():
        temp_len = right - left
        temp = [None] * temp_len
        pos_l = left
        pos_r = split
        pos_t = 0
        while pos_t < temp_len:
            if pos_r == right or pos_l != split and ask(arr[pos_l], arr[pos_r]):
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
arr = list(range(1, n + 1))
mergesort(arr, 0, n)
print(0, end=' ')
for i in arr:
    print(i, end=' ')
