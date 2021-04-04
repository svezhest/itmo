package expression;

import expression.exceptions.OverflowException;

public class CheckedMultiply extends AbstractBinaryOperation {
    public CheckedMultiply(CommonExpression firstExpression, CommonExpression secondExpression) {
        super(firstExpression, secondExpression);
    }

    @Override
    public int getLevel() {
        return 2;
    }

    @Override
    public String getSymbol() {
        return "*";
    }

    @Override
    public boolean isAssociative() {
        return false;
    }

    private int abs(int a) {
        return a < 0 ? -a : a;
    }
    @Override
    public int oper(int a, int b) {
        int res = a * b;
        if (a > 0) {
            if (b > 0 && Integer.MAX_VALUE / a < b ||
                b < 0 && Integer.MIN_VALUE / a > b) {
                throw new OverflowException("Multiplication overflow");
            }
        } else {
            if (b > 0 && Integer.MIN_VALUE / b > a ||
                    b < 0 && Integer.MAX_VALUE / b > a) {
                throw new OverflowException("Multiplication overflow");
            }
        }
        return res;
    }
}