from ba9g import suffix_array
from tqdm import tqdm


def common_prefix(a, b):
    res = 0
    for (ch_1, ch_2) in zip(a, b):
        if ch_1 != ch_2:
            break
        res += 1
    return res


if __name__ == '__main__':
    with open('rosalind_ba9d.txt', 'r') as f:
        text = f.readline()
        suf = suffix_array(text)
        maxline = ''
        for (n, idx) in tqdm(enumerate(suf)):
            if n > 0:
                t = common_prefix(text[suf[n]:], text[suf[n - 1]:])
                if t > len(maxline):
                    maxline = text[suf[n]:suf[n] + t]
        print(maxline)
