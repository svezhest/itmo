package queue;

import static java.lang.Integer.min;

// :NOTE: Unchecked warnings
public class ArrayQueue extends AbstractQueue {
    private int head;
    private Object[] elements = new Object[5];

    protected void enqueueImpl(final Object element) {
        ensureCapacity(size() + 1);
        elements[(head + size() + elements.length) % elements.length] = element;
    }

    // :NOTE: контракт?
    private void ensureCapacity(final int capacity) {
        if (capacity > elements.length) {
            elements = toArray(capacity * 2);
            head = 0;
        }
    }

    private Object[] toArray(final int arraySize) {
        final Object[] temp = new Object[arraySize];
        final int toEnd = min(size(), elements.length - head);
        System.arraycopy(elements, head, temp, 0, toEnd);
        System.arraycopy(elements, 0, temp, toEnd, size() - toEnd);
        return temp;
    }

    protected Object dequeueImpl() {
        final Object value = element();
        elements[head] = null;
        head = (head + 1) % elements.length;
        return value;
    }


    protected Object elementImpl() {
        return elements[head];
    }

    protected void clearImpl() {
        head = 0;
        elements = new Object[5];
    }

    @Override
    public Object[] toArray() {
        return toArray(size());
    }

    @Override
    public Queue newQueue() {
        return new ArrayQueue();
    }

    //PRE:    element != null && queue != null
    //POST:    queue'.size() = queue.size() + 1 && for all i in range (1, queue'.size()) queue'[i] = queue[i]
    //    queue'[0] = element
    protected void pushImpl(final Object element) {
        ensureCapacity(size() + 1);
        head = (elements.length + head - 1) % elements.length;
        elements[head] = element;
    }

    //PRE:    queue.size > 0 && queue != null
    //POST:    queue'.size() = queue.size() - 1 && for all i in range (0, queue'.size()) queue'[i] = queue[i]
    //    R = queue[size() - 1]
    protected Object removeImpl() {
        final Object value = peek();
        elements[(elements.length + head + size() - 1) % elements.length] = null;
        return value;
    }

    //PRE:    queue.size > 0 && queue != null
    //POST:    queue'.size() = queue.size() && for all i in range (0, queue'.size()) queue'[i] = queue[i]
    //    R = queue[size() - 1]
    protected Object peekImpl() {
        return elements[(elements.length + head + size() - 1) % elements.length];
    }
}
