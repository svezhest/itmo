import sys

sys.stdin = open('input.txt', 'r')
sys.stdout = open('output.txt', 'w')


class Matrix:
    def __init__(self, n, m):
        assert n > 0 and m > 0
        self.size = (n, m)
        self.__matrix = [None] * n
        for i in range(n):
            self.__matrix[i] = [None] * m

    def set(self, str, col, value):
        assert str < self.size[0] and col < self.size[1]
        self.__matrix[str][col] = value

    def mult_by(self, k):
        for i in range(self.size[0]):
            for j in range(self.size[1]):
                self.__matrix[i][j] *= k

    def get(self, str, col):
        return self.__matrix[str][col]

    def list2matrix(self, nums):
        k = 0
        for i in range(self.size[0]):
            for j in range(self.size[1]):
                self.__matrix[i][j] = nums[k]
                k += 1

    def matrix2list(self):
        nums = [None] * (self.size[0] * self.size[1])
        k = 0
        for i in range(self.size[0]):
            for j in range(self.size[1]):
                nums[k] = self.__matrix[i][j]
                k += 1
        return nums

    def cut_matrix(self, from_str, from_col, to_str, to_col):
        assert to_str < self.size[0] and to_col < self.size[1]
        n = to_str - from_str
        m = to_col - from_col
        new_m = Matrix(n, m)
        for i in range(n):
            for j in range(m):
                new_m.__matrix[i][j] = self.__matrix[i + from_str][j + from_col]
        return new_m

    def det(self):
        assert self.size[0] == self.size[1]
        if self.size[0] == 2:
            return self.__matrix[0][0] * self.__matrix[1][1] - self.__matrix[0][1] * self.__matrix[1][0]
        answ = 0
        for k in range(self.size[0]):
            temp = Matrix(self.size[0] - 1, self.size[1] - 1)
            for i in range(self.size[0]):
                if i == k:
                    continue
                for j in range(0, self.size[1] - 1):
                    if i > k:
                        temp.__matrix[i - 1][j] = self.__matrix[i][j + 1]
                    else:
                        temp.__matrix[i][j] = self.__matrix[i][j + 1]
            answ += (self.__matrix[k][0] * temp.det() * (-1) ** (k % 2))
        return answ


def matr_sum(a, b):
    assert a.size == b.size
    matr = Matrix(a.size[0], a.size[1])
    length = a.size[0] * a.size[1]
    al = a.matrix2list()
    bl = b.matrix2list()
    nums = [al[i] + bl[i] for i in range(length)]
    matr.list2matrix(nums)
    return matr


def matr_mult(a, b):
    assert a.size[1] == b.size[0]
    c = Matrix(a.size[0], b.size[1])
    for str in range(a.size[0]):
        for col in range(b.size[1]):
            r = 0
            for i in range(a.size[1]):
                r += a.get(str, i) * b.get(i, col)
            c.set(str, col, r)
    return c


def transp(matr):
    t = Matrix(matr.size[1], matr.size[0])
    for i in range(matr.size[0]):
        for j in range(matr.size[1]):
            t.set(j, i, matr.get(i, j))
    return t


def create_matrix():
    n, m = map(int, input().split())
    matr = Matrix(n, m)
    matr.list2matrix(list(map(float, input().split())))
    return matr


# a = create_matrix()
# b = create_matrix()
# t = matr_mult(a, b)
# print(t.matrix2list())
# useful for checking homework

alfa, beta = map(float, input().split())
a = create_matrix()
b = create_matrix()
c = create_matrix()
d = create_matrix()
f = create_matrix()

try:
    a.mult_by(alfa)
    b = transp(b)
    b.mult_by(beta)
    r = matr_sum(a, b)
    r = transp(r)
    r = matr_mult(c, r)
    r = matr_mult(r, d)
    f.mult_by(-1)
    r = matr_sum(r, f)
    print(1)
    print(r.size[0], r.size[1])
    for i in r.matrix2list():
        print(i, end=' ')

except AssertionError:
    print(0)

sys.stdin.close()
sys.stdout.close()
