package expression.implementations;

import expression.AbstractBinaryOperation;
import expression.CommonExpression;
import expression.calculators.Calculator;

public class CheckedAdd<E extends Number> extends AbstractBinaryOperation<E> {
    public CheckedAdd(CommonExpression<E> firstExpression, CommonExpression<E> secondExpression, Calculator<E> calculator) {
        super(firstExpression, secondExpression, calculator);
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

    public E oper(E a, E b) {
        return calculator.add(a, b);
    }
}