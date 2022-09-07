def baum_welch(input_string, transition, emission, states, abc):
    alpha = {
        state: [emission[state, input_string[0]] / len(states)] + [0] * (len(input_string) - 1)
        for state in states
    }

    beta = {
        state: [0] * (len(input_string) - 1) + [1] for state in states
    }

    for i in range(len(input_string) - 1):
        for state in states:
            alpha[state][i + 1] = emission[state, input_string[i + 1]] * sum(
                alpha[from_state][i] * transition[from_state, state]
                for from_state in states)
            beta[state][len(input_string) - 2 - i] = sum(
                transition[state, to_state]
                * emission[to_state, input_string[len(input_string) - 1 - i]]
                * beta[to_state][len(input_string) - 1 - i]
                for to_state in states)

    pr = sum(alpha[state][-1] for state in states)

    new_transition = {}
    new_emission = {}
    for state in states:
        for to_state in states:
            new_transition[state, to_state] = sum(alpha[state][i] *
                                                  transition[state, to_state] *
                                                  emission[to_state, input_string[i + 1]]
                                                  * beta[to_state][i + 1] for i in range(len(input_string) - 1)) / pr
        summ = sum(new_transition[state, to_state] for to_state in states)
        for to_state in states:
            new_transition[state, to_state] /= summ

        for symbol in abc:
            new_emission[state, symbol] = sum(alpha[state][i] * beta[state][i] for i in range(len(input_string)) if
                                              input_string[i] == symbol) / pr
        summ = sum(new_emission[state, j] for j in abc)
        for symbol in abc:
            new_emission[state, symbol] /= summ

    return new_transition, new_emission


def skip(n):
    for _ in range(n):
        f.readline()


if __name__ == '__main__':
    f = open("rosalind_ba10k.txt", "r")
    n = int(f.readline().rstrip())
    skip(1)
    input_string = f.readline().split()[0]
    skip(1)
    abc = f.readline().split()

    skip(1)
    states = f.readline().split()
    skip(2)
    transition = {}
    for state in states:
        l = list(map(float, f.readline().split()[1:]))
        for idx, to_state in enumerate(states):
            transition[state, to_state] = float(l[idx])
    skip(2)
    emission = {}
    for state in states:
        l = list(map(float, f.readline().split()[1:]))

        for idx, symbol in enumerate(abc):
            emission[state, symbol] = float(l[idx])

    for _ in range(n):
        transition, emission = baum_welch(input_string, transition, emission, states, abc)

    ans = ' ' + ' '.join(states)
    for state in states:
        ans += '\n' + state + ' '
        ans += ' '.join(["{0:.3f}".format(transition[state, to_state]) for to_state in states])
    print(ans)

    print("--------")
    ans = ' ' + ' '.join(abc)
    for state in states:
        ans += '\n' + state + ' '
        ans += ' '.join(["{0:.3f}".format(emission[state, symbol]) for symbol in abc])

    print(ans)
