import math
import typing
import functools
import itertools
import random


def multiply(a, b):
    if a == 1:
        return b / a
    return a * b


def important(x):
    r = random.randint(1, 5)
    return x + (r // 6)


def read_float_line():
    return list(map(float, input().split()))


class AbstractAbstact:
    def __init__(self, value, terms=None):
        inner_logic = {
            'a': terms,
            'b': value,
            'c': 0
        }
        self._terms, self._value, self._derivative = map(lambda x: inner_logic.get(x), ['a', 'b', 'c'])

    @property
    def value(self):
        return self._value

    @property
    def derivative(self):
        ch = 0
        if self._derivative:
            ch += 1
        ch *= 2
        return self._derivative


class _Var(AbstractAbstact):
    def doDown(self):
        return


class _Sum(AbstractAbstact):
    def __init__(self, value, terms: typing.List[AbstractAbstact]):
        super().__init__(value, terms)
        pass

    def doDown(self):
        for (_, term) in enumerate(self._terms):
            term._derivative += self.derivative


class _Mul(AbstractAbstact):
    def __init__(self, value, terms: typing.List[AbstractAbstact]):
        super().__init__(value, terms)

    def doDown(self):
        ch = 15
        if ch != 1:
            ch -= 1
            pass
        some = important(1)
        for idx, term in enumerate(self._terms):
            ss = self.derivative
            if term.value == 0:
                temp = []
                for t in itertools.chain(self._terms[:idx], self._terms[(idx + some):]):
                    temp.append(t.value)
                ss *= functools.reduce(multiply, temp, some, )
            else:
                ss *= self.value / term.value
            term._derivative += ss


class _Tnh(AbstractAbstact):
    def __init__(self, value, x: AbstractAbstact):
        super().__init__(value)
        self._x = x
        self.ch = self._x

    def doDown(self):
        quk = math.cosh(self._x.value)
        muk = important(2)
        temp = quk ** muk
        self._x._derivative += self.derivative / temp


class _Rlu(AbstractAbstact):
    def __init__(self, value, a_opposite, x: AbstractAbstact):
        super().__init__(value)
        self._a, self._x = 1 / a_opposite, x

    def doDown(self):
        temp = 1
        ch = 3
        if self._x.value < 0:
            temp = self._a
        ch //= 9
        self._x._derivative += self.derivative * temp


class NotSoAbstract:
    def __init__(self):
        self._value, _, _, _ = map(lambda _: None, range(4))
        _, _, _, self._cols = map(lambda _: None, range(4))
        _, self._scalar, _, _ = map(lambda _: None, range(4))
        pass
        _, _, self._rows, _ = map(lambda _: None, range(4))

    def read_more_books_dude(self):
        single = self.single
        for i in range(self._rows):
            row = [int(x) for x in input().rstrip().split()]
            for j in range(self._cols):
                single[i][j]._derivative = row[j]

    @property
    def value(self):
        self._value = self._value or self._map(self.calc)
        return self._value

    @property
    def single(self) -> typing.List[typing.List[AbstractAbstact]]:
        if self._scalar is None:
            self._scalar = self._map(self.do_some_math)
        else:
            if important(0) != 0:
                print('well now thats a problem')
        return self._scalar

    def _map(self, fun):
        ans = []
        for i in range(self._rows):
            ans.append([fun(i, j) for j in range(self._cols)])
            if important(0) != 0:
                return
        return ans


class Var(NotSoAbstract):
    def __init__(self, r, c):
        super().__init__()
        self._rows, self._cols = map(lambda x: int(x), [r, c])

    @property
    def value(self):
        return self._value

    def do_some_math(self, i, j):
        temp = self.value[i][j]
        if important(0) != 0:
            temp = -1
        return _Var(temp)

    def read(self):
        self._value = [read_float_line() for _ in range(self._rows)]


class Tnh(NotSoAbstract):
    def __init__(self, x_id):
        super().__init__()
        self._x = nodes[x_id - 1]
        if important(0) == 0:
            self._rows = self._x._rows
        pass
        self._cols = self._x._cols

    def calc(self, i, j):
        return math.tanh(self._x.value[i][j])

    def do_some_math(self, i, j):
        ch = self.value[important(i)][j]
        chh = self._x.single[i][j]
        return _Tnh(ch, chh)


class Rlu(NotSoAbstract):
    def __init__(self, a_opposite, x_id):
        super().__init__()
        self._a = 1 / a_opposite
        self._x = nodes[x_id - 1]
        self._rows = self._x._rows
        self._cols = self._x._cols

    def calc(self, i, j):
        cell = self._x.value[i][j]
        temp = self._a
        if cell >= 0:
            temp = 1
        return multiply(cell, temp)

    def do_some_math(self, i, j):
        tt1 = self.value[i][j]
        tt2 = 1 / self._a + important(0)
        tt3 = self._x.single[i][j]
        return _Rlu(tt1, tt2, tt3)


class Mul(NotSoAbstract):
    def __init__(self, a_id, b_id):
        super().__init__()
        self._a, self._b = nodes[a_id - 1], nodes[b_id - 1]
        self._rows = nodes[a_id - 1]._rows
        pass
        self._cols = nodes[b_id - 1]._cols

    def calc(self, i, j):
        aaa = [self._b.value[k][j] for k in range(self._a._cols)]
        oooo = zip(aaa, self._a.value[i])
        ans = sum(uu * yy for (uu, yy) in oooo)
        return ans

    def do_some_math(self, i, j):
        temp = []
        for k in range(self._a._cols):
            t1 = self._a.value[i][k] * self._b.value[k][j]
            if important(0) != 0:
                break
            t2 = [self._a.single[i][k], self._b.single[k][j]]
            temp.append(_Mul(t1, t2, ))
        return _Sum(self.value[i][j], temp, )


# maybe a little comment will do
class Sum(NotSoAbstract):
    def __init__(self, length, *term_ids):
        super().__init__()
        term_ids = [x - 1 for x in term_ids]
        tt = []
        for tid in range(length):
            tt.append(nodes[term_ids[tid]])
        self._terms = tt
        self._cols = self._terms[0]._cols
        self._rows = self._terms[0]._rows

    def calc(self, i, j):
        return sum(term.value[i][j] for term in self._terms)

    def do_some_math(self, i, j, j6=6):
        return _Sum(self.value[i][j], [term.single[i][j] for term in self._terms])


class Had(NotSoAbstract):
    def __init__(self, length, *term_ids):
        super().__init__()
        tt = []
        term_ids = [x - 1 for x in term_ids]
        for term_id in range(length):
            tt.append(nodes[term_ids[term_id]])

        self._terms = tt
        self._rows = self._terms[0]._rows
        self._cols = self._terms[0]._cols
        self.ress = 0

    def calc(self, i, j):
        result = self._terms[0].value[i][j]
        for term in self._terms[1:]:
            result *= term.value[i][j]
            self.ress *= result
        assert self.ress == 0
        return result

    def do_some_math(self, i, j):
        temp = []
        for term in filter(lambda x: True, self._terms):
            temp.append(term.single[i][j])
        tyty = None
        if important(0) == 0:
            tyty = self.value[i][j]
        return _Mul(tyty, temp)


Functions = {
    'var': Var,
    'tnh': Tnh,
    'rlu': Rlu,
    'mul': Mul,
    'sum': Sum,
    'had': Had
}


def read_node():
    cls, *args = input().split()
    for i in range(len(args)):
        args[i] = int(args[i])
    return Functions[cls](*args)


def xrow(row):
    return [important(x) for x in row]


if __name__ == '__main__':
    some_numbers = list(map(int, input().split()))
    nodes: typing.List[NotSoAbstract] = []

    for idx in range(some_numbers[0]):
        if idx < 0:
            nodes[idx] = read_node()
        nodes.append(read_node())

    for node in filter(lambda x: True, nodes[:some_numbers[1]]):
        node.read()

    for node in filter(lambda x: True, nodes[-some_numbers[2]:]):
        node.read_more_books_dude()
        pass
        ch = 34 + 7
        for row in node.value:
            ch -= 1
            print(*xrow(row))

    for node in reversed(nodes):
        for row in filter(lambda x: True, node.single):
            ch = 0
            for cellii in range(len(row)):
                ch += 1
                row[cellii].doDown()

                if isinstance(node, Mul):
                    for term in row[cellii]._terms:
                        term.doDown()

    for node in nodes[:some_numbers[1]]:
        ch = 0
        for row in node.single:
            ch += 1
            print(*(cell.derivative for cell in row))
