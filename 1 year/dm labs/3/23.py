import sys

sys.stdin = open('nextvector.in', 'r')
sys.stdout = open('nextvector.out', 'w')


s = input()
l = len(s)
i = l - 1
while s[i] != '1':
    i -= 1
    if i == -1:
        break
if i != -1:
    print(s[:i] + '0' + '1' * (l - i - 1))
else:
    print('-')
i = l - 1
while s[i] != '0':
    i -= 1
    if i == -1:
        break
if i != -1:
    print(s[:i] + '1' + '0' * (l - i - 1))
else:
    print('-')
