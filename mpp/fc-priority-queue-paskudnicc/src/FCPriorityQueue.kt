import kotlinx.atomicfu.*
import java.util.*
import java.util.concurrent.ThreadLocalRandom

interface Task<E> : Runnable {
    fun isFinished() : Boolean
    fun getResult() : E?
}

class FCArray<R>(size : Int) {
    private val lock = atomic(false)
    private val array = atomicArrayOfNulls<Task<R>>(size)

    private fun tryLock() : Boolean {
        return !this.lock.value && this.lock.compareAndSet(false, true)
    }

    private fun unlock() {
        this.lock.compareAndSet(true, false)
    }

    fun doTask(task: Task<R>) : R? {
        var ind = ThreadLocalRandom.current().nextInt(0, array.size)
        while (!this.array[ind].compareAndSet(null, task)) {
            ind = ThreadLocalRandom.current().nextInt(0, array.size)
        }

        while (!task.isFinished()) {
            if (this.tryLock()) {
                for (i in 0 until array.size) {
                    val request = array[i].value
                    if (request != null && !request.isFinished()) {
                        request.run()
                    }
                }
                this.unlock()
                break
            }
        }

        this.array[ind].getAndSet(null)
        return task.getResult()
    }
}


class FCPriorityQueue<E : Comparable<E>> {
    private val queue = PriorityQueue<E>()

    private class TaskImpl<E>(private val runnable: (TaskImpl<E>) -> Unit) : Task<E> {
        var finished = false
        var res: E? = null

        override fun isFinished() = finished
        override fun getResult() = res
        override fun run() = runnable(this)
    }

    private val poolSize = 20

    private val taskPool = FCArray<E>(poolSize)

    /**
     * Retrieves the element with the highest priority
     * and returns it as the result of this function;
     * returns `null` if the queue is empty.
     */
    fun poll(): E? {
        return taskPool.doTask(TaskImpl { env -> env.res = queue.poll(); env.finished = true; })
    }

    /**
     * Returns the element with the highest priority
     * or `null` if the queue is empty.
     */
    fun peek(): E? {
        return taskPool.doTask(TaskImpl { env -> env.res = queue.peek(); env.finished = true; })
    }

    /**
     * Adds the specified element to the queue.
     */
    fun add(element: E) {
        taskPool.doTask(TaskImpl { env -> queue.add(element); env.finished = true; })
    }
}
