package queue;

import java.util.function.Function;
import java.util.function.Predicate;

public abstract class AbstractQueue<E> implements Queue<E> {
    private int size;

    @Override
    public void enqueue(final E element) {
        assert element != null;
        enqueueImpl(element);
        size++;
    }

    protected abstract void enqueueImpl(E element);

    @Override
    public E dequeue() {
        assert size > 0;
        final E value = dequeueImpl();
        size--;
        return value;
    }

    @Override
    public Queue<E> filter(final Predicate<E> predicate) {
        final Function<E, E> function = x -> x;
        return change(function, predicate);
    }

    @Override
    public Queue<E> map(final Function<E, E> function) {
        final Predicate<E> predicate = x -> true;
        return change(function, predicate);
    }

    private Queue<E> change(final Function<E, E> function, final Predicate<E> predicate) {
        final Queue<E> newQueue = newQueue();
        @SuppressWarnings("unchecked") final E[] elements = (E[]) toArray();
        for (int i = 0; i < size(); i++) {
            final E element = elements[i];
            if (predicate.test(element)) {
                newQueue.enqueue(function.apply(element));
            }
        }
        return newQueue;
    }

    protected abstract E dequeueImpl();

    @Override
    public E element() {
        assert size > 0;
        return elementImpl();
    }

    protected abstract E elementImpl();

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public void clear() {
        size = 0;
        clearImpl();
    }

    protected abstract void clearImpl();

    // :NOTE: Контракт?
    public void push(final E element) {
        assert element != null;
        pushImpl(element);
        size++;
    }

    protected abstract void pushImpl(E element);

    public E remove() {
        // :NOTE: Контракт?
        final E value = removeImpl();
        size--;
        return value;
    }

    protected abstract E removeImpl();

    public E peek() {
        assert size() > 0;
        return peekImpl();
    }

    protected abstract E peekImpl();
}
