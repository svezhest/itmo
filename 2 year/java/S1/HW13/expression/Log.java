package expression;

import expression.exceptions.LogArgumentException;

public class Log extends AbstractBinaryOperation {
    public Log(CommonExpression firstExpression, CommonExpression secondExpression) {
        super(firstExpression, secondExpression);
    }

    @Override
    public String getSymbol() {
        return "//";
    }

    @Override
    public int oper(int first, int second) {
        if (first <= 0) {
            throw new LogArgumentException("log x is defined for x > 0");
        } else if (second <= 0) {
            throw new LogArgumentException("log(a)b is defined for b > 0");
        } else if (second == 1) {
            throw new LogArgumentException("log(a)b is not defined for b = 1");
        }
        int res = 0;
        first /= second;
        while (first > 0) {
            first /= second;
            res++;
        }
        return res;
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
