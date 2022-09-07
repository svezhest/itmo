package expression.implementations;

import expression.AbstractUnaryOperation;
import expression.CommonExpression;
import expression.calculators.Calculator;

public class Count<E extends Number> extends AbstractUnaryOperation<E> {

    public Count(CommonExpression<E> expression, Calculator<E> calculator) {
        super(expression, calculator);
    }

    @Override
    public int getLevel() {
        return 0;
    }

    @Override
    public E function(E x) {
        return calculator.count(x);
    }

    @Override
    public String getSymbol() {
        return "count";
    }
}
