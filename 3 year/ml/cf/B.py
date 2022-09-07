k = int(input())

cm = []
for i in range(k):
    cm.append(list(map(int, input().split())))

tp = [cm[i][i] for i in range(k)]
fp = [sum([(cm[i][j] if i != j else 0) for i in range(k)]) for j in range(k)]
fn = [sum([(cm[i][j] if i != j else 0) for j in range(k)]) for i in range(k)]
count = sum([sum(item for item in row) for row in cm])
predicted = [tp[i] + fp[i] for i in range(k)]
precision = [tp[i] / (predicted[i]) if predicted[i] != 0 else 0 for i in range(k)]
real = [tp[i] + fn[i] for i in range(k)]
recall = [tp[i] / (real[i]) if real[i] != 0 else 0 for i in range(k)]
f1 = [2 * precision[i] * recall[i] / (precision[i] + recall[i]) if precision[i] + recall[i] != 0 else 0 for i in
      range(k)]
weights = [real[i] / count for i in range(k)]
wAveragedP = sum([precision[i] * weights[i] for i in range(k)])
wAveragedR = sum([tp[i] / count for i in range(k)])  # optimize
averageF1 = sum([f1[i] * weights[i] for i in range(k)])
macroF1 = 2 * wAveragedP * wAveragedR / (wAveragedP + wAveragedR) if wAveragedP + wAveragedR != 0 else 0
wTP = sum([tp[i] * weights[i] for i in range(k)])
wFN = sum([fn[i] * weights[i] for i in range(k)])
wFP = sum([fp[i] * weights[i] for i in range(k)])
wPrecision = wTP / (wTP + wFP) if wTP + wFP != 0 else 0
wRecall = wTP / (wTP + wFN) if wTP + wFN != 0 else 0
microF1 = 2 * wPrecision * wRecall / (wPrecision + wRecall) if wPrecision + wRecall != 0 else 0

print(microF1)
print(macroF1)
print(averageF1)
