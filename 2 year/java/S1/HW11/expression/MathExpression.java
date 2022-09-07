package expression;

public abstract class MathExpression implements MathObject {
    private MathObject left;
    private MathObject right;
    private Operation operation;

    protected MathExpression(MathObject r, MathObject l, String type) {
        this.left = r;
        this.right = l;
        this.operation = new Operation(type);
    }

    public Priority getPriority() {
        return operation.getPriority();
    }

    @Override
    public String toMiniString() {
        StringBuilder sb = new StringBuilder();

        if (left.getPriority().getValue() >= getPriority().getValue()) {
            sb.append(left.toMiniString());
        } else {
            sb.append('(').append(left.toMiniString()).append(')');
        }

        sb.append(' ').append(operation).append(' ');

        if (getPriority().getValue() < right.getPriority().getValue()
                || (getPriority().getValue() == right.getPriority().getValue()
                && !right.getPriority().isOrdered() && !getPriority().isOrdered())) {
            sb.append(right.toMiniString());
        } else {
            sb.append('(').append(right.toMiniString()).append(')');
        }
        return sb.toString();
    }

    @Override
    public String toString() {
        return "(" + left + " " + operation + " " + right + ")";
    }

    @Override
    public boolean equals(Object obj) {
        if (obj != null && obj.getClass() == getClass()) {
            return left.equals(((MathExpression) obj).left) && right.equals(((MathExpression) obj).right);
        }
        return false;
    }

    @Override
    public int evaluate(int x) {
        return operation.doOperation(left.evaluate(x), right.evaluate(x));
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return operation.doOperation(left.evaluate(x, y, z), right.evaluate(x, y, z));
    }

    @Override
    public int hashCode() {
        return 3389 * left.hashCode() + 57 * 57 * right.hashCode() + getClass().hashCode();
    }
}
