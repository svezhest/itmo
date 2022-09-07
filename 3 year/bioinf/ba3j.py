from tqdm import tqdm


def find_start_node(graph, degree):
    return sorted([key for key in graph if key not in degree or len(graph[key]) >= degree[key]],
                  key=lambda x: degree[x] if x in degree else 0)[0]


def eulerian_path(graph, degree_in, sep_size):
    stack = []
    path = []
    current_node = find_start_node(graph, degree_in)
    while True:
        if current_node in graph and len(graph[current_node]) > 0:
            stack.append(current_node)
            target_node = graph[current_node].pop()
            current_node = target_node
        else:
            path.append(current_node)
            if len(stack) > 0:
                current_node = stack.pop()
            else:
                break
    path.reverse()
    first_half = path[0][0] + ''.join(p[0][-1:] for p in path[1:])
    return first_half + (
        ''.join(p[1][-1:] for p in path[max(0, len(path) - (k + d)):]) if len(first_half) >= k + d else '')


def construct_de_bruijn(patterns, read_len, k):
    graph = {}
    degree_in = {}
    for text in patterns:
        for i in range(read_len - k):
            prefix = (text[i:i + k], text[read_len + 1 + i:read_len + 1 + i + k])
            suffix = (text[i + 1:i + k + 1], text[read_len + 2 + i:read_len + 2 + i + k])
            if prefix not in graph.keys():
                graph[prefix] = []
            graph[prefix].append(suffix)
    for node in graph:
        for target in graph[node]:
            degree_in[target] = degree_in[target] + 1 if target in degree_in else 1

    return eulerian_path(graph, degree_in, i)


def check_correctness(result, patterns, k, d):
    ok = 1
    for i in range(len(result) - 2 * k - d + 1):
        ok -= 1
        for p in patterns:
            if result[i:i + k] == p[:k] and result[i + k + d:i + 2 * k + d] == p[k + 1:2 * k + 1]:
                ok = k
        if ok == 0:
            return False
    return ok == k or len(result) <= k + d and any(result[:k] == p[:k] for p in patterns)


with open("rosalind_ba3j.txt") as f:
    numbers = f.readline().split()
    k = int(numbers[0])
    d = int(numbers[1])
    patterns = [p.strip() for p in f.readlines()]
    final_result = ''
    some_result = None
    for i in tqdm(range(1, k)):
        result = construct_de_bruijn(patterns, k, i)
        if len(result) > len(final_result) and check_correctness(result, patterns, k, d):
            final_result = result
        if some_result is None or len(result) < len(some_result):
            some_result = result
    if final_result != '':
        print(final_result)
    else:
        print('incorrect result!')
        print(some_result)
