def numToEdgeStart(n):
    return n * 2 + 1 if n > 0 else (-n) * 2


def numToEdgeEnd(n):
    return n * 2 if n > 0 else (-n) * 2 + 1


def edgeStartToNum(n):
    return -n // 2 if n % 2 == 0 else n // 2


def edgeEndToNum(n):
    return n // 2 if n % 2 == 0 else - (n - 1) // 2


def genomeToEdges(genome):
    edges = [0] * (len(genome) + 1) * 2
    edges[1] = numToEdgeEnd(genome[0])
    edges[numToEdgeEnd(genome[0])] = 1
    for i in range(len(genome) - 1):
        edges[numToEdgeStart(genome[i])] = numToEdgeEnd(genome[i + 1])
        edges[numToEdgeEnd(genome[i + 1])] = numToEdgeStart(genome[i])
    edges[numToEdgeStart(genome[-1])] = 0
    edges[0] = numToEdgeStart(genome[-1])
    return edges


def edgesToGenome(edges):
    genome = []
    i = 0
    visited = [False] * len(edges)
    visited[0] = True
    while sum(len(g) for g in genome) < len(edges) // 2 - 1:
        if visited[i]:
            genome.append([])
            for j in range(len(edges)):
                if not visited[j] and edges[j] != 0:
                    i = j
                    break
        visited[i] = True
        if edges[i] != 0:
            genome[-1].append(edgeEndToNum(edges[i]))
            i = numToEdgeStart(genome[-1][-1])
            visited[numToEdgeEnd(genome[-1][-1])] = True
    return genome


def edgesToCycles(edges1, edges2):
    cycles = []
    red = True
    visited = [False] * len(edges1)
    for v in range(len(edges1)):
        if visited[v]:
            continue
        cycles.append([])
        while not visited[v]:
            visited[v] = True
            if red:
                new_v = edges1[v]
            else:
                new_v = edges2[v]
            red = not red
            cycles[-1].append([v, new_v])
            v = new_v
        red = True
    return cycles


def reduceNumberOfCycles(cycles):
    new_cycles = []
    done = False
    for c in cycles:
        if not done and len(c) >= 4:
            new_cycles.append([[c[2][0], c[0][1]], c[1]])
            new_cycles.append([[c[0][0], c[2][1]]] + c[3:])
            done = True
        else:
            new_cycles.append(c)
    return new_cycles


def cyclesToEdges(cycles):
    edges_len = sum(len(c) for c in cycles)
    edges1 = [0] * edges_len
    edges2 = [0] * edges_len
    for c in cycles:
        red = True
        for e in c:
            if red:
                edges1[e[0]] = e[1]
                edges1[e[1]] = e[0]
            else:
                edges2[e[0]] = e[1]
                edges2[e[1]] = e[0]
            red = not red
    return edges1, edges2


def twoBreaksFind(genome1, genome2):
    edges1 = genomeToEdges(genome1)
    edges2 = genomeToEdges(genome2)
    cycles = edgesToCycles(edges1, edges2)
    path = [[genome1]]
    while sum(len(c) - 2 for c in cycles) > 0:
        cycles = reduceNumberOfCycles(cycles)
        new_edges, _ = cyclesToEdges(cycles)
        path.append(edgesToGenome(new_edges))
    return path


# it has to be correct
if __name__ == '__main__':
    with open('rosalind_ba6d.txt') as f:
        dataset = f.read().split('\n')
        text1 = list(map(int, dataset[0].strip('(').strip(')').split()))
        text2 = list(map(int, dataset[1].strip('(').strip(')').split()))

        path = twoBreaksFind(text1, text2)

        for line in path:
            for chromosome in line:
                print('(' + ' '.join('+' + str(c) if c > 0 else str(c) for c in chromosome) + ')', end='')
            print()
