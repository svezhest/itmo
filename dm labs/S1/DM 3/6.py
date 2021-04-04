import sys

sys.stdin = open('vectors.in', 'r')
sys.stdout = open('vectors.out', 'w')

n = int(input())

v = [None] * n
v[0] = "0", "1"
v[1] = "00", "01", "10"
for i in range(2, n):
    v[i] = ["0" + v0 for v0 in v[i - 1]] + ["10" + v1 for v1 in v[i - 2]]

print(len(v[n - 1]), *v[n - 1], sep='\n')
