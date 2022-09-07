package expression.implementations;

import expression.AbstractBinaryOperation;
import expression.CommonExpression;
import expression.calculators.Calculator;

public class Min<E extends Number> extends AbstractBinaryOperation<E> {
    public Min(CommonExpression<E> firstExpression, CommonExpression<E> secondExpression, Calculator<E> calculator) {
        super(firstExpression, secondExpression, calculator);
    }

    @Override
    public E oper(E a, E b) {
        return calculator.min(a, b);
    }

    @Override
    public boolean isAssociative() {
        return true;
    }

    @Override
    public int getLevel() {
        return 0;
    }

    @Override
    public String getSymbol() {
        return "min";
    }
}
