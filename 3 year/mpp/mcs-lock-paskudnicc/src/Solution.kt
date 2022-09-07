import java.util.concurrent.atomic.AtomicReference


class Solution(private val env: Environment) : Lock<Solution.Node> {
    private val last = AtomicReference<Node?>(null)

    override fun lock(): Node {
        val my = Node() // сделали узел

        val prev = last.getAndSet(my) ?: return my
        prev.next.set(my)
        while (my.locked.value) this.env.park()

        return my // вернули узел
    }

    override fun unlock(node: Solution.Node) {
        if (node.next.value == null) {
            if (last.compareAndSet(node, null)) return
            else while (node.next.get() == null);
        }
        node.next.get()!!.locked.set(false)
        this.env.unpark(node.next.value.thread)
    }

    class Node {
        val thread: Thread = Thread.currentThread() // запоминаем поток, которые создал узел
        val locked = AtomicReference(true)
        val next = AtomicReference<Node>(null)
    }
}