package stack;

import kotlinx.atomicfu.AtomicArray;
import kotlinx.atomicfu.AtomicBoolean;
import kotlinx.atomicfu.AtomicRef;

import java.util.Random;

public class StackImpl implements Stack {
    private static class Node {
        final AtomicRef<Node> next;
        final int x;

        Node(int x, Node next) {
            this.next = new AtomicRef<>(next);
            this.x = x;
        }
    }

    // head pointer

    private static class IntWrapper {
        final int x;

        IntWrapper(int x) {
            this.x = x;
        }
    }

    private final AtomicRef<Node> head = new AtomicRef<>(null);
    private final int THREAD_NUM = 8;
    private final int ARRAY_SIZE = THREAD_NUM * 4;
    private final int ATTEMPTS = ARRAY_SIZE * 500;
    private final AtomicArray<IntWrapper> eliminationArray = new AtomicArray<>(ARRAY_SIZE);
    private final Random random = new Random();

    @Override
    public void push(int x) {
        int pos = random.nextInt(ARRAY_SIZE);
        boolean settled = false;
        boolean eliminated = false;
        IntWrapper t = new IntWrapper(x);
        for (int i = 0; i < ATTEMPTS; i++) {
            if (settled) {
                if (eliminationArray.get(pos).getValue() == null) {
                    eliminated = true;
                    break;
                }
            } else {
                if (eliminationArray.get(pos).compareAndSet(null, t)) {
                    settled = true;
                } else {
                    pos = (pos + 1) % ARRAY_SIZE;
                }
            }
        }
        if (settled && !eliminationArray.get(pos).compareAndSet(t, null)) {
                eliminated = true;
        }
        if (!eliminated) {
            while (true) {
                Node curHead = head.getValue();
                Node newHead = new Node(x, curHead);
                if (head.compareAndSet(curHead, newHead)) {
                    return;
                }
            }
        }
    }

    @Override
    public int pop() {
        int pos = random.nextInt(ARRAY_SIZE);
        for (int i = 0; i < ATTEMPTS; i++) {
            IntWrapper t = eliminationArray.get(pos).getValue();
            if (t == null) {
                pos = (pos + 1) % ARRAY_SIZE;
                continue;
            }
            if (eliminationArray.get(pos).compareAndSet(t, null)) {
                return t.x;
            }
        }
        while (true) {
            Node curHead = head.getValue();
            if (curHead == null) return Integer.MIN_VALUE;
            if (head.compareAndSet(curHead, curHead.next.getValue())) {
                return curHead.x;
            }
        }
    }
}
