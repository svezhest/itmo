def bwt(text):
    assert text[-1] == '$'
    temp = text + text[:-1]
    return ''.join(
        key[len(text) - 1] for (_, key) in sorted(enumerate(temp[i:] for i in range(len(text))), key=lambda x: x[1]))


if __name__ == '__main__':
    print(bwt('acaacg$'))
