import kotlinx.atomicfu.*

class DynamicArrayImpl<E> : DynamicArray<E> {
    private val core = atomic(Core<E>(INITIAL_CAPACITY, 0))

    override fun get(index: Int): E {
        if (index >= size) throw IllegalArgumentException()
        return core.value.array[index].value!!.value
    }

    override fun put(index: Int, element: E) {
        if (index >= size) throw IllegalArgumentException()
        while (true) {
            val core = core.value
            val value = core.array[index].value
            if (value is Moved<*>) {
                core.next.value ?: core.next.compareAndSet(null, Core(2 * core.array.size, core.array.size))
                val next: Core<E> = core.next.value ?: continue
                update(core, next)
                this.core.compareAndSet(core, next)
            } else {
                if (core.array[index].compareAndSet(value, Active(element))) {
                    return
                }
            }
        }
    }

    override fun pushBack(element: E) {
        while (true) {
            val size = size
            val core = core.value
            if (core.array.size <= size) {
                core.next.value ?: core.next.compareAndSet(null, Core(2 * core.array.size, core.array.size))
                val next = core.next.value ?: return
                update(core, next)
                this.core.compareAndSet(core, next)
            } else if (core.array[size].compareAndSet(null, Active(element))) {
                core.size.incrementAndGet()
                return
            }
        }
    }

    private fun update(core: Core<E>, next:Core<E>) {
        for (i in 0 until core.array.size) {
            var value = core.array[i].value

            while (value is Active<E> && !core.array[i].compareAndSet(value, Moved(value.value))) {
                value = core.array[i].value
            }
            if (value != null) {
                next.array[i].compareAndSet(null, Active(value.value))
            }
        }
    }

    override val size: Int get() = core.value.size.value
}

private interface Node<E>{
    val value: E
}
private class Moved<E>(override val value: E) : Node<E>
private class Active<E>(override val value: E): Node<E>

private class Core<E>(
    capacity: Int, size : Int
) {
    val array = atomicArrayOfNulls<Node<E>>(capacity)
    val next: AtomicRef<Core<E>?> = atomic(null)
    val size = atomic(size)
}

private const val INITIAL_CAPACITY = 1 // DO NOT CHANGE ME