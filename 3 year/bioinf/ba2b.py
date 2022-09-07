from itertools import product


def hamming_distance(a, b, a_offset):
    if len(a) < len(b) + a_offset:
        return 9999999999
    return sum(1 if a[i + a_offset] != bb else 0 for (i, bb) in enumerate(b))


if __name__ == '__main__':
    f = open('rosalind_ba2b.txt').readlines()
    k = int(f[0].rstrip())
    dna_list = [i.rstrip() for i in f[1:]]

    res = min([[sum([min([hamming_distance(dna, pattern, offset) for offset in range(len(dna) - k)]) for dna in dna_list]),
                pattern] for pattern in [''.join(i) for i in product(['A', 'C', 'G', 'T'], repeat=k)]])
    print(res[1])
