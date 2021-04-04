package expression;

import expression.exceptions.OverflowException;

public class CheckedNegate extends AbstractUnaryOperation {
    public CheckedNegate(CommonExpression expression) {
        super(expression);
    }

    @Override
    public int getLevel() {
        return 3;
    }

    @Override
    public int function(int a) {
        if (a == Integer.MIN_VALUE) {
            throw new OverflowException("negation of min value");
        }
        return -a;
    }

    @Override
    public String getSymbol() {
        return "-";
    }
}