package queue;

import java.util.function.Function;
import java.util.function.Predicate;

public interface Queue<E> {

    //PRE:    element != null, queue != null
    //POST:    queue'.size() = queue.size() + 1 && for all i in range (0, queue.size()) queue'[i] = queue[i]
    //    queue'[queue.size()] = element
    void enqueue(E element);

    //PRE:    queue != null, queue.size > 0
    //POST:    queue'.size() = queue.size() - 1 && for all i in range (1, queue.size()) queue'[i - 1] = queue[i]
    //    R = queue[0]
    E dequeue();

    //PRE: queue != null, for all i in range(0, queue.size()) predicate.test(queue[i]) returns true or false
    //POST:    newQueue.size() = quantity of elements of queue which make predicate.test be true, for all i in range(0, newQueue.size()) newQueue[i] = queue[j] &&
    //    for all i1, all i2 in range (0, newQueue.size()) exist j1, j2 and if i1 <= i2 j1 <= j2
    //    for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size() && R = newQueue
    Queue<E> filter(Predicate<E> predicate);

    // :NOTE: function(queue[i]) != null
    //PRE:    size() > 0 && queue != null
    //POST:  newQueue.size() = queue'.size() = queue.size() && for all j in range(0, queue'.size) newQueue[j] = function(queue[j]), queue'[j] = queue[j]
    Queue<E> map(Function<E, E> function);

    //PRE:    queue.size() > 0 && queue != null
    //POST:    for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    //    R = queue[0]
    E element();

    //PRE:  queue != null
    //POST:  array.size() = queue'.size() = queue.size() && for all j in range(0, queue'.size) array[j] = queue'[j] = queue[j] && R = array
    Object[] toArray();

    //PRE:  queue != null
    //POST:  newQueue.size() = queue'.size() = queue.size() && for all j in range(0, queue'.size) newQueue[j] = queue'[j] = queue[j] && R = newQueue
    Queue<E> newQueue();

    //PRE:    queue != null
    //POST:    for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    //    R = queue.size()
    int size();

    //PRE:    queue != null
    //POST:    for all i in range (0, queue.size()) queue'[i] = queue[i] && queue'.size() = queue.size()
    //    R = queue.size() == 0
    boolean isEmpty();

    //PRE:    queue != null
    //POST:    queue'.size() = 0
    void clear();
}
