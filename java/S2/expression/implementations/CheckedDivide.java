package expression.implementations;

import expression.AbstractBinaryOperation;
import expression.CommonExpression;
import expression.calculators.Calculator;

public class CheckedDivide<E extends Number> extends AbstractBinaryOperation<E> {
    public CheckedDivide(CommonExpression<E> firstExpression, CommonExpression<E> secondExpression, Calculator<E> calculator) {
        super(firstExpression, secondExpression, calculator);
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
    public E oper(E a, E b) {
        return calculator.divide(a, b);
    }
}