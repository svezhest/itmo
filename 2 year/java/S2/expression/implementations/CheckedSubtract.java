package expression.implementations;

import expression.AbstractBinaryOperation;
import expression.CommonExpression;
import expression.calculators.Calculator;

public class CheckedSubtract<E extends Number> extends AbstractBinaryOperation<E> {
    public CheckedSubtract(CommonExpression<E> firstExpression, CommonExpression<E> secondExpression, Calculator<E> calculator) {
        super(firstExpression, secondExpression, calculator);
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
    public E oper(E a, E b) {
        return calculator.subtract(a, b);
    }
}