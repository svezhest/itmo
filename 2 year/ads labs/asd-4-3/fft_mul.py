'''
это я написал спустя год, независимо, когда у меня беспричинно возникло желание понять fft
хотя и не писалось для кфа наверняка подойдет под одну из тасок
видимо в том году меня покусали скаков и сорокин,
иначе не получается объяснить битово темплейтный трэшак в тасках.
а самое ржачное что я забыл все в 0 и все равно написал так же
'''


import math
import random
import numpy
from tokenize import Number

class approach_1:
    def eval_poly(x, p):
        res = 0
        for ind, a in enumerate(p):
            res += a * x ** ind
        return res

    def multiplication(a, b):
        res = [0] * (len(a) + len(b) - 1)
        for i, x in enumerate(a):
            for j, y in enumerate(b):
                res[i + j] += x * y
        return res

def fft(p : list[Number], inverse = False) -> list[Number]:
    if not float.is_integer(math.log2(len(p))):
        p += [0] * round(2 ** (math.ceil(math.log2(len(p)))) - 2 ** math.log2(len(p)))
    n = len(p)
    if n == 1:
        return p
    w = math.e ** (2 * math.pi * 1j / n) 
    if inverse:
        w = w ** -1
    p0, p1 = p[::2], p[1::2]
    y0, y1 = fft(p0, inverse), fft(p1, inverse)
    y = [0] * n
    for i in range(n // 2):
        y[i] = y0[i] + (w ** i) * y1[i]
        y[i + n // 2] = y0[i] - (w ** i) * y1[i]
    if inverse:
        y = [x / 2 for x in y]
    return y


class approach_2:
    def multiplication(a, b):
        n = len(a) + len(b) - 1
        n = 2 ** (math.ceil(math.log2(n)))
        a += [0] * (n - len(a))
        b += [0] * (n - len(b))
        def simplify(x):
            if abs(x.imag) < 10e-10:
                res = x.real
                if abs(res - round(res)) < 10e-10:
                    return round(res)
                return round(res, 5)
            return x
        res = list(map(simplify, fft([x * y for x, y in zip(fft(a), fft(b))], True)))
        for ind, val in enumerate(reversed(res)):
            if val:
                return res[:-ind]
        return [0]
        

# class approach_3:
#     def multiplication(a, b):
#         return numpy.fft.ifft([x * y for x, y in zip(numpy.fft.fft(a), numpy.fft.fft(b))])


a = numpy.random.random_sample(random.randint(2,5)).tolist()
b = numpy.random.random_sample(random.randint(2,5)).tolist()

print("a = {a},\nb = {b}".format(a = a, b = b))
print(approach_1.multiplication(a, b))
print(approach_2.multiplication(a, b))
# print(approach_3.multiplication(a, b))


