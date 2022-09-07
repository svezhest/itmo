class ConsistentHashImpl<K> : ConsistentHash<K> {
    private var nodes: List<Node> = ArrayList()

    class Node(val hash: Int, val shard: Shard)

    override fun getShardByKey(key: K): Shard {
        val hash = key.hashCode()


        var l = 0
        var r = nodes.size - 1
        while (l < r - 1) {
            val m = (l + r) / 2
            if (hash <= nodes[m].hash) {
                r = m
            } else {
                l = m
            }
        }

        return if (hash <= nodes[l].hash) {
            nodes[l].shard
        } else {
            if (hash <= nodes[r].hash) {
                nodes[r].shard
            } else {
                nodes[0].shard
            }
        }
    }

    override fun addShard(newShard: Shard, vnodeHashes: Set<Int>): Map<Shard, Set<HashRange>> {
        nodes = (nodes + vnodeHashes.map { x -> Node(x, newShard) }).sortedWith(compareBy { x -> x.hash })
        return toMap(newShard, false)
    }

    override fun removeShard(shard: Shard): Map<Shard, Set<HashRange>> {
        return toMap(shard, true)
    }

    private fun toMap(shard: Shard, shouldRemove: Boolean): HashMap<Shard, HashSet<HashRange>> {
        var idx = 0
        while (idx < nodes.size && nodes[idx].shard == shard) {
            idx++
        }

        val map: HashMap<Shard, HashSet<HashRange>> = HashMap()
        if (idx != nodes.size) {

            var prevID = nodes[idx].hash

            for (i in 1..nodes.size) {
                val curID = nodes[(i + idx) % nodes.size].hash
                val curShard = nodes[(i + idx) % nodes.size].shard
                val nextShard = nodes[(i + idx + 1) % nodes.size].shard

                if (curShard == shard) {
                    if (nextShard != shard) {
                        if (!map.contains(nextShard)) {
                            map[nextShard] = HashSet()
                        }
                        map[nextShard]!!.add(HashRange(prevID + 1, curID))
                    }
                } else {
                    prevID = curID
                }
            }
        }
        if (shouldRemove) {
            nodes = nodes.filter { x -> x.shard != shard }
        }
        return map
    }

}