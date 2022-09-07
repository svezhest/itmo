package expression;

import expression.calculators.Calculator;

public abstract class AbstractUnaryOperation<E extends Number> implements CommonExpression<E>, UnaryFunction<E> {
    protected Calculator<E> calculator;
    private CommonExpression<E> expression;


    public AbstractUnaryOperation(CommonExpression<E> expression, Calculator<E> calculator) {
        this.expression = expression;
        this.calculator = calculator;
    }

    @Override
    public String toString() {
        return toMiniString();
    }

    @Override
    public String toMiniString() {
        String end = "";
        String start = "";
        if (expression instanceof AbstractBinaryOperation) {
            start = "(";
            end = ")";
        }
        return start + expression.toMiniString() + end;
    }

    @Override
    public E evaluate(int x, int y, int z) {
        return function(expression.evaluate(x, y, z));
    }
}