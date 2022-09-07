import random
from tqdm import tqdm


def dna_to_num(letter):
    if letter == 'A':
        return 0
    if letter == 'C':
        return 1
    if letter == 'G':
        return 2
    if letter == 'T':
        return 3


def all_kmers(dna, k):
    return [dna[pos: pos + k] for pos in range(len(dna) - k)]


def profile_list(motifs):
    counts = []
    for batch in zip(*motifs):
        counts.append([batch.count(ch) for ch in ['A', 'C', 'G', 'T']])
    return counts


def find_motif(dna, profile, k):
    best_score = None
    best_kmer = None
    for kmer in all_kmers(dna, k):
        kmer_idx = [dna_to_num(l) for l in kmer]
        kmer_score = sum(profile[i][kmer_idx[i]] for i in range(k))
        if best_score is None or kmer_score > best_score:
            best_score = kmer_score
            best_kmer = kmer
    return best_kmer


def randomized_motif_search(dna_list, k, t):
    motifs = []
    for dna in dna_list:
        pos = random.randrange(0, len(dna) - k)
        motifs.append(dna[pos: pos + k])

    best_motifs = motifs
    while True:
        profile = profile_list(motifs)
        motifs = [find_motif(dna, profile, k) for dna in dna_list]

        if score(motifs) > score(best_motifs):
            best_motifs = motifs
        else:
            return best_motifs


def score(motifs):
    return sum([max(batch) for batch in profile_list(motifs)])


f = open('rosalind_ba2f.txt').readlines()
k, t = map(int, f[0].rstrip().split(' '))
dna_list = [i.rstrip() for i in f[1:]]
best_motif = []
best_score = None
for i in tqdm(range(1000)):
    motif = randomized_motif_search(dna_list, k, t)
    motif_score = score(motif)
    if best_score is None or motif_score > best_score:
        best_score = motif_score
        best_motif = motif
print(*best_motif, sep='\n')

