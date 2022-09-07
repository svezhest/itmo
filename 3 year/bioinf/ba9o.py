from tqdm import tqdm
from ba2b import hamming_distance

# omg ok i resign. i swtg i tried MANY TIMES to apply lecture thing to this problem
# ima use fact enough cpu to do it below 5 min
if __name__ == '__main__':
    with open('rosalind_ba9o.txt', 'r') as f:
        text = f.readline().rstrip().lower()
        patterns = [x.rstrip().lower() for x in f.readline().rstrip().split()]
        d = int(f.readline())
        res = []
        for pattern in tqdm(patterns):
            for (i, _) in enumerate(text):
                if hamming_distance(text, pattern, i) <= d:
                    res.append(i)

        print(*sorted(res))
