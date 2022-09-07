package expression.calculators;

import expression.exceptions.OverflowException;
import expression.exceptions.ZeroDivisionException;

public class CheckedIntegerCalculator implements Calculator<Integer> {

    @Override
    public Integer add(final Integer a, final Integer b) {
        if ((a > 0 && b > 0 && a + b - Integer.MAX_VALUE > 0) ||
                (a < 0 && b < 0 && a + b + Integer.MAX_VALUE + 1 < 0)) {
            throw new OverflowException("Adding overflow");
        }
        return (a + b);
    }

    @Override
    public Integer subtract(final Integer a, final Integer b) {
        if ((a < 0 || (b < 0 && -Integer.MAX_VALUE + a > b)) &&
                (a >= 0 || (b > 0 && a + Integer.MAX_VALUE + 1 < b))) {
            throw new OverflowException("Subtraction overflow");
        }
        return a - b;
    }

    @Override
    public Integer multiply(final Integer a, final Integer b) {
        final int res = a * b;
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

    @Override
    public Integer divide(final Integer a, final Integer b) {
        if (b == 0) {
            throw new ZeroDivisionException("Cannot divide by 0");
        }
        if (a == Integer.MIN_VALUE) {
            if (b == -1) {
                throw new OverflowException("Max value divided by -1");
            }
        }
        return a / b;
    }

    @Override
    public Integer negate(final Integer x) {
        if (x == Integer.MIN_VALUE) {
            throw new OverflowException("Negation of min value");
        }
        return -x;
    }

    @Override
    public Integer count(final Integer first) {
        return Integer.bitCount(first);
    }

    @Override
    public Integer max(final Integer a, final Integer b) {
        return a > b ? a : b;
    }

    @Override
    public Integer min(final Integer a, final Integer b) {
        return a < b ? a : b;
    }

    @Override
    public Integer parse(final String s) {
        return Integer.parseInt(s);
    }
}
