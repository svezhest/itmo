package expression;

import expression.exceptions.OverflowException;
import expression.exceptions.PowArgumentException;

public class Pow extends AbstractBinaryOperation {
    public Pow(CommonExpression firstExpression, CommonExpression secondExpression) {
        super(firstExpression, secondExpression);
    }

    @Override
    public String getSymbol() {
        return "**";
    }

    @Override
    public int oper(int first, int second) {
        if (second < 0) {
            throw new PowArgumentException("a ^ b is defined for b >= 0");
        } else if (second == 0) {
            if (first == 0) {
                throw new PowArgumentException("0 ^ 0 = ???");
            }
            return 1;
        } else if (second == 1 || first == 1 || first == 0) {
            return first;
        }
        int r = 1;
        boolean cursed = false;
        while (second != 0) {
            if (second % 2 == 1) {
                if (cursed) {
                    throw new OverflowException("Pow overflow");
                }
                r = checkedMultiply(r, first);
            }
            second /= 2;
            if ((first * first) / first != first) {
                cursed = true;
            }
            first *= first;
        }
        return r;
    }

    private int checkedMultiply(int a, int b) {
        int r = a * b;
        if (r / b != a) {
            throw new OverflowException("Pow overflow");
        }
        return r;
    }

    @Override
    public boolean isAssociative() {
        return true;
    }

    @Override
    public int getLevel() {
        return 3;
    }
}
