package expression;

public class Variable implements MathObject {
    private String var;

    public Variable(String var) {
        this.var = var;
    }

    @Override
    public int evaluate(int x) {
        return x;
    }

    @Override
    public Priority getPriority() {
        return new Priority(PriorityLevels.HIGH, false);
    }

    @Override
    public String toMiniString() {
        return var;
    }

    @Override
    public String toString() {
        return var;
    }

    public boolean equals(Object obj) {
        if (obj != null && obj.getClass() == getClass()) {
            return var.equals(obj.toString());
        }
        return false;
    }

    public int hashCode() {
        return var.hashCode() * 3389;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        switch (var) {
            case("x"):
                return x;
            case("y"):
                return y;
            case("z"):
                return z;
            default:
                return -1;
        }
    }
}
