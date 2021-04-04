import sys

sys.stdin = open('nextbrackets.in', 'r')
sys.stdout = open('nextbrackets.out', 'w')

br = input()
l = len(br)
d = 0
ans = ''
for i in range(len(br) - 1, -1, -1):
    if br[i] == ')':
        d -= 1
    else:
        if d == -1:
            d = 0
        else:
            dd = 0
            ans = br[:i] + ')'
            for a in ans:
                if a == ')':
                    dd -= 1
                else:
                    dd += 1
            x = (l - len(ans) - dd) // 2
            ans += '(' * x + ')' * x
            ans += ')' * dd
            break
if ans == '':
    print('-')
else:
    print(ans)
