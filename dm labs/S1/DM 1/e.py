def find_depth(f, d, args_collection):
    dmax = d
    if args_collection[f]:
        for a in args_collection[f]:
            dmax = max(find_depth(a, d + 1, args_collection), dmax)
    return dmax


def create_function(results):
    return lambda a: results[a]


n = int(input())
nn = n + 1
elem = [None] * nn
args_collection = [None] * nn
links = []
for i in range(1, nn):
    s = [int(x) for x in input().split()]
    if s[0] == 0:

        links.append(i)
    else:
        elem[i] = create_function(input())
        args_collection[i] = s[1:]

print(find_depth(n, 0, args_collection))

val = [None] * nn

l = len(links)
_ = range(2 ** l)
l -= 1

for seed in _:
    i = l
    while i >= 0:
        val[links[i]] = seed % 2
        seed //= 2
        i -= 1

    for i in range(1, nn):
        if elem[i]:
            ind = 0
            for a in args_collection[i]:
                ind = ind * 2 + val[a]
            ind *= 2
            val[i] = int(elem[i](ind))

    print(val[n], end='')
