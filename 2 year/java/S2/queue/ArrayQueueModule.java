package queue;

import static java.lang.Integer.min;

// INV: for all i in range (0, queue.size()) queue[i] != null; queue.size() >= 0
public class ArrayQueueModule {
    private static int head, tail;
    private static Object[] elements = new Object[5];

    //PRE:    element != null
    //POST:    queue'.size() = queue.size() + 1 && for all i in range (0, queue.size()) queue'[i] = queue[i]
    //    queue'[queue.size()] = element
    public static void enqueue(Object element) {
        assert element != null;

        ensureCapacity(size() + 1);
        elements[tail] = element;
        tail = (tail + 1) % elements.length;
    }

    //PRE:    element != null
    //POST:    queue'.size() = queue.size() + 1 && for all i in range (1, queue'.size()) queue'[i] = queue[i]
    //    queue'[0] = element
    public static void push(Object element) {
        assert element != null;

        ensureCapacity(size() + 1);
        head = (elements.length + head - 1) % elements.length;
        elements[head] = element;
    }

    //PRE:    true
    //POST: for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    private static void ensureCapacity(int capacity) {
        if (capacity >= elements.length) {
            elements = toArray(capacity * 2);
            tail = capacity - 1;
            head = 0;
        }
    }

    //PRE:    arraySize >= 0
    //POST: for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    private static Object[] toArray(int arraySize) {
        Object[] temp = new Object[arraySize];
        int toEnd = min(size(), elements.length - head);
        System.arraycopy(elements, head, temp, 0, toEnd);
        System.arraycopy(elements, 0, temp, toEnd, size() - toEnd);
        return temp;
    }

    //PRE:    queue.size > 0
    //POST:    queue'.size() = queue.size() - 1 && for all i in range (1, queue.size()) queue'[i - 1] = queue[i]
    //    R = queue[0]
    public static Object dequeue() {
        Object value = element();
        elements[head] = null;
        head = (head + 1) % elements.length;
        return value;
    }

    //PRE:    queue.size > 0
    //POST:    queue'.size() = queue.size() - 1 && for all i in range (0, queue'.size()) queue'[i] = queue[i]
    //    R = queue[size() - 1]
    public static Object remove() {
        Object value = peek();
        tail = (elements.length + tail - 1) % elements.length;
        elements[tail] = null;
        return value;
    }


    //PRE:    queue.size > 0
    //POST:    queue'.size() = queue.size() && for all i in range (0, queue'.size()) queue'[i] = queue[i]
    //    R = queue[size() - 1]
    public static Object peek() {
        assert size() > 0;

        return elements[(elements.length + tail - 1) % elements.length];
    }

    //PRE:    queue.size() > 0
    //POST:    for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    //    R = queue[0]
    public static Object element() {
        assert size() > 0;
        return elements[head];
    }

    //PRE:    true
    //POST:    for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    //    R = queue.size()
    public static int size() {
        if (head <= tail) {
            return tail - head;
        }
        return tail + elements.length - head;
    }

    //PRE:    true
    //POST:    for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    //    R = queue.size() == 0
    public static boolean isEmpty() {
        return head == tail;
    }


    //PRE:    true
    //POST:   queue'.size() = 0
    public static void clear() {
        head = 0;
        tail = 0;
        elements = new Object[5];
    }

    //PRE:  true
    //POST:  array.size() = queue'.size() = queue.size() && for all j in range(0, queue'.size) array[j] = queue'[j] = queue[j] && R = array
    public static Object[] toArray() {
        return toArray(size());
    }
}
