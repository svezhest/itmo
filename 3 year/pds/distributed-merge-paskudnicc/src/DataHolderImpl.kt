import system.DataHolderEnvironment

class DataHolderImpl<T : Comparable<T>>(
    private val keys: List<T>,
    private val dataHolderEnvironment: DataHolderEnvironment
) : DataHolder<T> {
    private var checkpoint: Int = 0
    private var current: Int = 0

    override fun checkpoint() {
        checkpoint = current
    }

    override fun rollBack() {
        current = checkpoint
    }

    override fun getBatch(): List<T> {
        val res = ArrayList<T>()
        for (count in 0 until dataHolderEnvironment.batchSize) {
            if (current == keys.size) {
                break
            }
            res.add(keys[current])
            current++
        }
        return res
    }
}