def read_matrix_as_dict(arr):
    ans = {}
    for i in range(len(states)):
        line = [float(x) for x in f.readline().split()[1:]]
        for (ind, x) in enumerate(line):
            ans[(states[i], arr[ind])] = x
    return ans


def skip(n):
    for _ in range(n):
        f.readline()


def reverse_string(str):
    return ''.join(str[::-1])


if __name__ == '__main__':
    with open('rosalind_ba10c.txt', 'r') as f:
        input_string = f.readline().rstrip()
        skip(1)
        abc = f.readline().split()
        skip(1)
        states = f.readline().split()
        skip(2)
        t_matrix = read_matrix_as_dict(states)

        skip(2)
        e_matrix = read_matrix_as_dict(abc)

        scores = {(0, state): e_matrix[state, input_string[0]] * 1 / len(states) for state in states}
        next_states = {(0, state): '' for state in states}
        last_char = None
        for (idx, ch) in enumerate(input_string[1:]):
            for state in states:
                max_next_score = None
                for next_state in states:
                    temp = (scores[idx, next_state] * t_matrix[next_state, state], next_state)
                    if max_next_score is None or max_next_score < temp:
                        max_next_score = temp
                scores[idx + 1, state] = max_next_score[0] * e_matrix[state, ch]
                next_states[idx + 1, state] = max_next_score[1]
                if idx == len(input_string) - 2:
                    temp = (scores[idx + 1, state], state)
                    if last_char is None or temp > last_char:
                        last_char = temp

        ans = str(last_char[1])
        for i in range(len(input_string) - 1, -1, -1):
            ans += next_states[i, ans[-1]]

        print(reverse_string(ans))
