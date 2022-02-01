/**
 * @author :TODO: Kryukov Alexandr
 */
public class Solution implements AtomicCounter {
    // объявите здесь нужные вам поля
    private final Node root = new Node(0);
    private final ThreadLocal<Node> last = new ThreadLocal<>();

    public int getAndAdd(int x) {
        while (true) {
            if (last.get() == null) {
                last.set(root);
            }
            final int current = last.get().val;
            final int next = current + x;
            final Node newNode = new Node(next);
            final Node decision = last.get().consensus.decide(newNode);
            last.set(decision);
            if (last.get() == newNode) {
                return current;
            }
        }
    }

    // вам наверняка потребуется дополнительный класс
    private static class Node {
        final int val;
        final Consensus<Node> consensus;

        public Node(int value) {
            this.val = value;
            this.consensus = new Consensus<>();
        }
    }
}
