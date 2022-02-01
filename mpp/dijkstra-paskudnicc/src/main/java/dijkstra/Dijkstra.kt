package dijkstra

import kotlinx.atomicfu.atomic
import java.util.*
import java.util.concurrent.Phaser
import kotlin.Comparator
import kotlin.concurrent.thread
import java.util.concurrent.locks.ReentrantLock

private val NODE_DISTANCE_COMPARATOR = Comparator<Node> { o1, o2 -> Integer.compare(o1!!.distance, o2!!.distance) }

private class MultiQueue(threads: Int, val comparator: Comparator<Node>) {
    private val queuesNumber = maxOf(2 * threads, 2)
    private val queueList = List(queuesNumber) { Pair(PriorityQueue(queuesNumber, comparator), ReentrantLock(true)) }
    private val random = Random()

    fun add(element: Node) {
        while (true) {
            val randomQueue = queueList[random.nextInt(queuesNumber)]
            if (randomQueue.second.tryLock()) {
                val queue = randomQueue.first
                queue.offer(element)
                randomQueue.second.unlock()
                return
            }
        }
    }

    fun poll(): Node? {
        while (true) {
            val firstRandom = random.nextInt(queuesNumber)
            val firstQueue = queueList[firstRandom]
            if (firstQueue.second.tryLock()) {
                while (true) {
                    var secondRandom = random.nextInt(queuesNumber)
                    while (firstRandom == secondRandom) {
                        secondRandom = random.nextInt(queuesNumber)
                    }
                    val secondQueue = queueList[secondRandom]
                    if (secondQueue.second.tryLock()) {
                        val a = firstQueue.first.peek()
                        val b = secondQueue.first.peek()
                        val t = if (a == null) {
                            secondQueue.first.poll()
                        } else if (b == null) {
                            firstQueue.first.poll()
                        } else {
                            if (comparator.compare(a, b) < 0) {
                                firstQueue.first.poll()
                            } else {
                                secondQueue.first.poll()
                            }
                        }
                        firstQueue.second.unlock()
                        secondQueue.second.unlock()
                        return t
                    }
                }
            }
        }
    }
}

private val activeNodes = atomic(1)

// Returns `Integer.MAX_VALUE` if a path has not been found.
fun shortestPathParallel(start: Node) {
    val workers = Runtime.getRuntime().availableProcessors()
    // The distance to the start node is `0`
    start.distance = 0
    // Create a priority (by distance) queue and add the start node into it
    val q = MultiQueue(workers, NODE_DISTANCE_COMPARATOR) // TODO replace me with a multi-queue based PQ!
    q.add(start)
    // Run worker threads and wait until the total work is done
    val onFinish = Phaser(workers + 1) // `arrive()` should be invoked at the end by each worker
    activeNodes.lazySet(1)
    repeat(workers) {
        thread {
            while (true) {
                // TODO Write the required algorithm here,
                // TODO break from this loop when there is no more node to process.
                // TODO Be careful, "empty queue" != "all nodes are processed".
                val cur: Node = q.poll() ?: if (activeNodes.value == 0) break else continue
                for (e in cur.outgoingEdges) {
                    val newDistance = cur.distance + e.weight
                    while (true) {
                        val currentDistance = e.to.distance
                        if (currentDistance <= newDistance) {
                            break
                        } else {
                            if (!e.to.casDistance(currentDistance, newDistance)) {
                                continue
                            }
                            q.add(e.to)
                            activeNodes.incrementAndGet()
                            break
                        }
                    }
                }
                activeNodes.decrementAndGet()
            }
            onFinish.arrive()
        }
    }
    onFinish.arriveAndAwaitAdvance()
}