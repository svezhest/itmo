package expression.implementations;

import expression.AbstractUnaryOperation;
import expression.CommonExpression;
import expression.calculators.Calculator;

public class CheckedNegate<E extends Number> extends AbstractUnaryOperation<E> {
    public CheckedNegate(CommonExpression<E> expression, Calculator<E> calculator) {
        super(expression, calculator);
    }

    @Override
    public int getLevel() {
        return 3;
    }

    @Override
    public E function(E x) {
        return calculator.negate(x);
    }

    @Override
    public String getSymbol() {
        return "-";
    }
}