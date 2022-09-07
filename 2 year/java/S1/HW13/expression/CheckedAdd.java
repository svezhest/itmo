package expression;

import expression.exceptions.OverflowException;

public class CheckedAdd extends AbstractBinaryOperation {
    public CheckedAdd(CommonExpression firstExpression, CommonExpression secondExpression) {
        super(firstExpression, secondExpression);
    }

    @Override
    public int getLevel() {
        return 1;
    }

    @Override
    public String getSymbol() {
        return "+";
    }

    @Override
    public boolean isAssociative() {
        return false;
    }


    public int oper(int a, int b) {
        if ((a > 0 && b > 0 && a + b - Integer.MAX_VALUE > 0) ||
                (a < 0 && b < 0 && a + b + Integer.MAX_VALUE + 1 < 0)) {
            throw new OverflowException("Adding overflow");
        }
        return a + b;
    }
}