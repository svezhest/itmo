package expression;

public class Const implements MathObject {
    private Integer n;

    public Const(int number) {
        this.n = number;
    }

    @Override
    public int evaluate(int x) {
        return n;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return n;
    }

    @Override
    public Priority getPriority() {
        return new Priority(PriorityLevels.HIGH, false);
    }

    @Override
    public String toMiniString() {
        return n.toString();
    }

    @Override
    public String toString() {
        return n.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj != null && obj.getClass() == this.getClass()) {
            return n.equals(((Const) obj).evaluate(0));
        }
        return false;
    }

    public int hashCode() {
        return n;
    }
}
