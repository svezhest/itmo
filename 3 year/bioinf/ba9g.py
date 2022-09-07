def suffix_array(text):
    return [idx for (idx, _) in sorted(enumerate(text[i:] for i in range(len(text))), key=lambda x: x[1])]


if __name__ == '__main__':
    with open('rosalind_ba9g.txt') as f:
        text = f.readline().rstrip()
        print(*suffix_array(text), sep=', ')
