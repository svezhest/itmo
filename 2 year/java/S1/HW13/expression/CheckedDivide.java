package expression;

import expression.exceptions.OverflowException;
import expression.exceptions.ZeroDivisionException;

public class CheckedDivide extends AbstractBinaryOperation {
    public CheckedDivide(CommonExpression firstExpression, CommonExpression secondExpression) {
        super(firstExpression, secondExpression);
    }

    @Override
    public int getLevel() {
        return 2;
    }

    @Override
    public String getSymbol() {
        return "/";
    }

    @Override
    public boolean isAssociative() {
        return true;
    }

    @Override
    public int oper(int a, int b) {
        if (b == 0) {
            throw new ZeroDivisionException("cannot divide by 0");
        }
        if (a == Integer.MIN_VALUE) {
            if (b == -1) {
                throw new OverflowException("max value divided by -1");
            }
        }
        return a / b;
    }
}