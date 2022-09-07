package expression;

import expression.exceptions.OverflowException;

public class CheckedSubtract extends AbstractBinaryOperation {
    public CheckedSubtract(CommonExpression firstExpression, CommonExpression secondExpression) {
        super(firstExpression, secondExpression);
    }

    @Override
    public int getLevel() {
        return 1;
    }

    @Override
    public String getSymbol() {
        return "-";
    }

    @Override
    public boolean isAssociative() {
        return true;
    }


    @Override
    public int oper(int a, int b) {
        if ((a < 0 || (b < 0 && -Integer.MAX_VALUE + a > b)) &&
                (a >= 0 || (b > 0 && a + Integer.MAX_VALUE + 1 < b))) {
            throw new OverflowException("Subtraction overflow");
        }
        return a - b;
    }
}