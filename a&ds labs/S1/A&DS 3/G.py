skobki = input()
lenn = len(skobki)
inf = 99999999999999

dp = [None] * lenn
p = [None] * lenn
for i in range(lenn):
    dp[i] = [0] * lenn
    p[i] = [0] * lenn

for r in range(lenn):
    dp[r][r] = 1
    for l in range(r - 1, -1, -1):
        if skobki[l] == '{' and skobki[r] == '}' or \
                skobki[l] == '(' and skobki[r] == ')' or \
                skobki[l] == '[' and skobki[r] == ']':
            min = dp[l + 1][r - 1]
            # если скобки можно удалить
        else:
            min = inf
        mink = -1
        for k in range(l, r):
            if dp[k + 1][r] + dp[l][k] < min:
                min = dp[k + 1][r] + dp[l][k]
                mink = k
        # массив с разбиениями
        p[l][r] = mink
        dp[l][r] = min

answ = ""

def find(left, right):
    if left >= right:
        return ''
    if dp[left][right] == 0:
        return skobki[left:right + 1]
    if dp[left][right] - 1 != r - l:
        if p[left][right] == -1:
            # better not to remove l and r brackets
            return skobki[left] + find(left + 1, right - 1) + skobki[right]
        else:
            return find(left, p[left][right]) + find(p[left][right] + 1, right)


print(find(0, lenn - 1))
