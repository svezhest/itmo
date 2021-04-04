package expression;

public abstract class AbstractUnaryOperation implements CommonExpression, UnaryFunction {
    private CommonExpression expression;

    public AbstractUnaryOperation(CommonExpression expression) {
        this.expression = expression;
    }

    @Override
    public String toString() {
        return "(" + expression.toMiniString() + ")";
    }

    @Override
    public String toMiniString() {
        String end = "";
        String start = "";
        if (expression.getClass() == AbstractBinaryOperation.class) {
            start = "(";
            end = ")";
        }
        return start + expression.toMiniString() + end;
    }

    @Override
    public int evaluate(int x) {
        return function(expression.evaluate(x));
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return function(expression.evaluate(x, y, z));
    }
}