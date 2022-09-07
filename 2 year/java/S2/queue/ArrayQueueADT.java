package queue;

import static java.lang.Integer.min;

// INV: for all i in range (0, queue.size()) queue[i] != null; queue.size() >= 0
public class ArrayQueueADT {
    private int head, tail;
    private Object[] elements = new Object[5];

    //PRE:    element != null && queue != null
    //POST:    queue'.size() = queue.size() + 1 && for all i in range (0, queue.size()) queue'[i] = queue[i]
    //    queue'[queue.size()] = element
    public static void enqueue(ArrayQueueADT queue, Object element) {
        assert element != null;

        ensureCapacity(queue,size(queue) + 1);
        queue.elements[queue.tail] = element;
        queue.tail = (queue.tail + 1) % queue.elements.length;
    }


    //PRE:    element != null && queue != null
    //POST:    queue'.size() = queue.size() + 1 && for all i in range (1, queue'.size()) queue'[i] = queue[i]
    //    queue'[0] = element
    public static void push(ArrayQueueADT queue, Object element) {
        assert element != null;

        ensureCapacity(queue,size(queue) + 1);
        queue.head = (queue.elements.length + queue.head - 1) % queue.elements.length;
        queue.elements[queue.head] = element;
    }

    //PRE:    queue != null
    //POST: for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    private static void ensureCapacity(ArrayQueueADT queue, int capacity) {
        if (capacity >= queue.elements.length) {
            queue.elements = toArray(queue,capacity * 2);
            queue.tail = capacity - 1;
            queue.head = 0;
        }
    }

    //PRE:    arraySize >= 0 && queue != null
    //POST: for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    private static Object[] toArray(ArrayQueueADT queue, int arraySize) {
        Object[] temp = new Object[arraySize];
        int toEnd = min(size(queue), queue.elements.length - queue.head);
        System.arraycopy(queue.elements, queue.head, temp, 0, toEnd);
        System.arraycopy(queue.elements, 0, temp, toEnd, size(queue) - toEnd);
        return temp;
    }

    //PRE:    queue.size > 0 && queue != null
    //POST:    queue'.size() = queue.size() - 1 && for all i in range (1, queue.size()) queue'[i - 1] = queue[i]
    //    R = queue[0]
    public static Object dequeue(ArrayQueueADT queue) {
        Object value = element(queue);
        queue.elements[queue.head] = null;
        queue.head = (queue.head + 1) % queue.elements.length;
        return value;
    }

    //PRE:    queue.size > 0 && queue != null
    //POST:    queue'.size() = queue.size() - 1 && for all i in range (0, queue'.size()) queue'[i] = queue[i]
    //    R = queue[size() - 1]
    public static Object remove(ArrayQueueADT queue) {
        Object value = peek(queue);
        queue.tail = (queue.elements.length + queue.tail - 1) % queue.elements.length;
        queue.elements[queue.tail] = null;
        return value;
    }

    //PRE:    queue.size > 0 && queue != null
    //POST:    queue'.size() = queue.size() && for all i in range (0, queue'.size()) queue'[i] = queue[i]
    //    R = queue[size() - 1]
    public static Object peek(ArrayQueueADT queue) {
        assert size(queue) > 0;

        return queue.elements[(queue.elements.length + queue.tail - 1) % queue.elements.length];
    }

    //PRE:    queue.size() > 0 && queue != null
    //POST:    for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    //    R = queue[0]
    public static Object element(ArrayQueueADT queue) {
        assert size(queue) > 0;
        return queue.elements[queue.head];
    }

    //PRE:    queue != null
    //POST:    for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    //    R = queue.size()
    public static int size(ArrayQueueADT queue) {
        if (queue.head <= queue.tail) {
            return queue.tail - queue.head;
        }
        return queue.tail + queue.elements.length - queue.head;
    }

    //PRE:    queue != null
    //POST:    for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    //    R = queue.size() == 0
    public static boolean isEmpty(ArrayQueueADT queue) {
        return queue.head == queue.tail;
    }

    //PRE:    queue != null
    //POST:   queue'.size() = 0
    public static void clear(ArrayQueueADT queue) {
        queue.head = 0;
        queue.tail = 0;
        queue.elements = new Object[5];
    }

    //PRE:  queue != null
    //POST:  array.size() = queue'.size() = queue.size() && for all j in range(0, queue'.size) array[j] = queue'[j] = queue[j] && R = array
    public static Object[] toArray(ArrayQueueADT queue) {
        return toArray(queue, size(queue));
    }
}
