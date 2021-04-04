package queue;

public class LinkedQueue<E> extends AbstractQueue<E> {
    private class Node {
        Node next;
        E element;
        Node prev;

        Node(E element) {
            this.element = element;
            this.next = null;
            this.prev = null;
        }
    }

    private Node start = null;
    private Node end = null;

    @Override
    protected void enqueueImpl(E element) {
        Node newNode = new Node(element);
        if (size() != 0) {
            newNode.prev = end;
            end.next = newNode;
        } else {
            start = newNode;
        }
        end = newNode;
    }

    @Override
    protected E dequeueImpl() {
        E value = start.element;
        start = start.next;
        return value;
    }

    public Object[] toArray() {
        Object[] elements = new Object[size()];
        Node current = start;
        for (int i = 0; i < size(); i++) {
            elements[i] = current.element;
            current = current.next;
        }
        return elements;
    }

    @Override
    public Queue<E> newQueue() {
        return new LinkedQueue<E>();
    }

    @Override
    protected E elementImpl() {
        return start.element;
    }

    @Override
    protected void clearImpl() {
        start = null;
        end = null;
    }

    @Override
    protected void pushImpl(E element) {
        Node newNode = new Node(element);
        newNode.next = start;
        start.prev = newNode;
        start = newNode;
    }

    @Override
    protected E removeImpl() {
        E value = peek();
        end = end.prev;
        return value;
    }

    @Override
    protected E peekImpl() {
        return end.element;
    }
}
