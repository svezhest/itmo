from ba9g import suffix_array
from bwt import bwt

nucleotide_set = ['$', 'a', 'c', 'g', 't']


def nucleotide_idx(nucleotide):
    return nucleotide_set.index(nucleotide)


def calc_c(bwt_0):
    c = [len(bwt_0)] * len(nucleotide_set)
    for idx, x in enumerate(nucleotide_idx(nucleotide) for nucleotide in bwt_0):
        if c[x] == len(bwt_0):
            c[x] = idx
    return c


def calc_o(bwt):
    o = [[0] * len(bwt) for _ in nucleotide_set]
    for idx, x in enumerate(nucleotide_idx(nucleotide) for nucleotide in bwt):
        for _o in o:
            _o[idx] = _o[idx - 1]
        o[x][idx] += 1
    return o


def pattern_search(pattern, c, o, suffix_arr):
    r_l = 0
    r_h = len(o[0]) - 1
    for x in (nucleotide_idx(nucleotide) for nucleotide in pattern[::-1]):
        r_l = c[x] + (o[x][r_l - 1] if r_l - 1 >= 0 else 0)
        r_h = c[x] + o[x][r_h] - 1
    return [suffix_arr[idx] for idx in range(r_l, r_h + 1)]


if __name__ == '__main__':
    with open('rosalind_ba9h.txt') as f:
        text = f.readline().rstrip().lower()
        patterns = [line.rstrip().lower() for line in f.readlines()]

        text_1 = text + '$'
        text_bwt = bwt(text_1)
        suffixes = suffix_array(text_1)
        bwt_0 = [text_1[i] for i in suffixes]
        c = calc_c(bwt_0)
        o = calc_o(text_bwt)
        res = []
        for pattern in patterns:
            for x in pattern_search(pattern, c, o, suffixes):
                res.append(x)
        print(*sorted(res))
