n = int(input())
pow2 = 2 ** n

table = [None] * pow2
triangle = [None] * pow2

for i in range(pow2):
    table[i] = input()
    triangle[i] = [None] * (pow2 - i)
    triangle[0][i] = int(table[i][n + 1])

for i in range(1, pow2):
    for j in range(pow2 - i):
        triangle[i][j] = triangle[i - 1][j] ^ triangle[i - 1][j + 1]

for i in range(pow2):
    print(table[i][:n], triangle[i][0])
