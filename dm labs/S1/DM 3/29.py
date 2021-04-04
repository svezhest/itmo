import sys

sys.stdin = open('nextpartition.in', 'r')
sys.stdout = open('nextpartition.out', 'w')

razb = input().split('+')
n = razb[0].split('=')
razb = [int(x) for x in [n[1]] + razb[1:]]
n = int(n[0])
start = True
if len(razb) == 1 and razb[0] == n:
    print('No solution')
else:
    need = razb.pop() - 1
    razb[-1] += 1
    x = razb[-1]
    while need != 0 and need - x < 0:
        x += 1
        razb[-1] += 1
        need -= 1
    while need - x >= x:
        razb.append(x)
        need -= x
    if need != 0:
        razb.append(need)
    print(n, '=', sep='', end='')
    print(*razb, sep='+')


    ((()))
    (()())
    (())()
    ()(())
    ()()()