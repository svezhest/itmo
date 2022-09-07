def additive_phylogeny(tree, matrix, idx):
    if idx == 1:
        tree[0][idx], tree[idx][0] = matrix[0][idx], matrix[idx][0]
    else:
        dist = {}
        parents = {}
        limb_l, i, j = calc_limb_length(matrix, idx)
        current_distance = matrix[i][idx] - limb_l
        dist[i] = 0
        q = [i]
        while q:
            current_node = q[0]
            for node in tree[current_node]:
                if node not in dist:
                    dist[node] = dist[current_node] + tree[current_node][node]
                    parents[node] = current_node
                    if j == node:
                        prev = node
                        while current_distance < dist[prev]:
                            current_node = prev
                            prev = parents.get(current_node)
                        if current_distance == dist[prev]:
                            for _i, _j in [(prev, idx), (idx, prev)]:
                                tree[_i][_j] = limb_l
                        else:
                            tree.append(dict())
                            for _i, _j in [(idx, len(tree) - 1), (len(tree) - 1, idx)]:
                                tree[_i][_j] = limb_l
                            tree[prev].pop(current_node)
                            tree[current_node].pop(prev)
                            for _i, _j, _ans in [
                                (prev, len(tree) - 1, current_distance - dist[prev]),
                                (len(tree) - 1, prev, current_distance - dist[prev]),
                                (current_node, len(tree) - 1, dist[current_node] - current_distance),
                                (len(tree) - 1, current_node, dist[current_node] - current_distance),
                            ]:
                                tree[_i][_j] = _ans
                        return
                    else:
                        q.append(node)
            q.pop(0)


def sign(x):
    return 1 if x > 0 else -1


def calc_limb_length(matrix, ind):
    j = ind - sign(ind)
    minn = None
    for i in range(j + 1):
        if i != ind:
            temp = ((matrix[j][ind] + matrix[ind][i] - matrix[j][i]) // 2, i, j)
            if minn is None or temp < minn:
                minn = temp
    return minn


if __name__ == '__main__':
    with open('rosalind_ba7c.txt', 'r') as f:
        n = int(f.readline())
        matrix = list(map(list, [map(int, f.readline().rstrip().split()) for _ in range(n)]))

        tree = [{} for _ in range(n)]

        for ind in range(1, n):
            additive_phylogeny(tree, matrix, ind)

        idx = 0
        for dict_collection in tree:
            for dict, w in dict_collection.items():
                print(idx, end='')
                print('->', end='')
                print(dict, end='')
                print(':', end='')
                print(w)
            idx += 1
