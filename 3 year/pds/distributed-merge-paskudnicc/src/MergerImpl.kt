import system.MergerEnvironment

class MergerImpl<T : Comparable<T>>(
    private val mergerEnvironment: MergerEnvironment<T>,
    prevStepBatches: Map<Int, List<T>>?
) : Merger<T> {

    private val currentBatches: HashMap<Int, List<T>>

    init {
        if (prevStepBatches != null) {
            currentBatches = prevStepBatches.toMap(HashMap())
        } else {
            currentBatches = HashMap()
            for (i in 0 until mergerEnvironment.dataHoldersCount) {
                currentBatches[i] = mergerEnvironment.requestBatch(i)
            }
        }
    }

    class ComPair<T : Comparable<T>>(val value: T, val idx: Int) : Comparable<ComPair<T>> {
        override fun compareTo(other: ComPair<T>): Int {
            return this.value.compareTo(other.value)
        }
    }

    override fun mergeStep(): T? {

        try {
            val minEl = currentBatches.minOf { e -> ComPair(e.value.first(), e.key) }
            val minList = currentBatches[minEl.idx]!!

            if (minList.size <= 1) {
                val newList = mergerEnvironment.requestBatch(minEl.idx)
                if (newList.isEmpty()) {
                    currentBatches.remove(minEl.idx)
                } else {
                    currentBatches[minEl.idx] = newList
                }
            } else {
                currentBatches[minEl.idx] = minList.subList(1, minList.size)
            }
            return minEl.value
        } catch (e: NoSuchElementException) {
            return null
        }
    }

    override fun getRemainingBatches(): Map<Int, List<T>> {
        return currentBatches
    }
}