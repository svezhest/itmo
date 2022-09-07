package linked_list_set;

import kotlinx.atomicfu.AtomicRef;

public class SetImpl implements Set {
    private abstract static class Next {
    }

    private static class Node extends Next {
        AtomicRef<Next> next;
        int x;

        Node(int x, Next next) {
            this.next = new AtomicRef<>(next);
            this.x = x;
        }
    }

    private static class Removed extends Next {
        final Node next;

        Removed(Node next) {
            this.next = next;
        }
    }

    private static class Window {
        Node cur;
        Node next;
    }

    private final Node head = new Node(Integer.MIN_VALUE, new Node(Integer.MAX_VALUE, null));

    /**
     * Returns the {@link Window}, where cur.x < x <= next.x
     */
    private Window findWindow(int x) {
        retry:
        while (true) {
            Window w = new Window();
            w.cur = head;
            w.next = (Node) w.cur.next.getValue();

            while (true) {
//                w.cur -- w.next? -- removed(w.next.next) | w.next.next
                Next node = w.next.next.getValue();
                if (node instanceof Removed) {
                    // remove w.next
                    if (!w.cur.next.compareAndSet(w.next, ((Removed) node).next)) {
                        continue retry;
                    }
                    w.next = ((Removed) node).next;
                } else {
                    if (x <= w.next.x) {
                        break;
                    }
                    w.cur = w.next;
                    Next next = w.cur.next.getValue();
                    if (next instanceof Removed) {
                        continue retry;
                    } else {
                        w.next = (Node) next;
                    }
                }
            }
            return w;
        }
    }

    @Override
    public boolean add(int x) {
        while (true) {
            Window w = findWindow(x);
            if (w.next.x == x) {
                return false;
            }
            Node node = new Node(x, w.next);
            if (w.cur.next.compareAndSet(w.next, node)) {
                return true;
            }
        }
    }

    @Override
    public boolean remove(int x) {
        while (true) {
            Window w = findWindow(x);
            if (w.next.x != x) {
                return false;
            }
            Next node = w.next.next.getValue();
            if (node instanceof Removed) {
                return false;
            }
            if (w.next.next.compareAndSet(node, new Removed((Node) node))) {
                w.cur.next.compareAndSet(w.next, node);
                return true;
            }
        }
    }

    @Override
    public boolean contains(int x) {
        Window w = findWindow(x);
        return w.next.x == x;
    }
}