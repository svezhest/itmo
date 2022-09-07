package expression;

import expression.calculators.Calculator;

public abstract class AbstractBinaryOperation<E extends Number> implements CommonExpression<E>, BinaryFunction<E> {
    protected Calculator<E> calculator;
    private CommonExpression<E> firstExpression;
    private CommonExpression<E> secondExpression;

    public AbstractBinaryOperation(CommonExpression<E> firstExpression, CommonExpression<E> secondExpression, Calculator<E> calculator) {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.calculator = calculator;
    }

    @Override
    public String toMiniString() {
        StringBuilder into = new StringBuilder();
        checkBrackets(into, firstExpression, false);
        into.append(getSymbol());
        checkBrackets(into, secondExpression, true);
        return into.toString();
    }

    private void checkBrackets(StringBuilder into, CommonExpression exp, boolean isSecond) {
        String end = "";
        if (getLevel() > exp.getLevel()
                || (isAssociative() && getLevel() == exp.getLevel() && isSecond)) {
            into.append('(');
            end = ")";
        }
        into.append(exp.toMiniString());
        into.append(end);
    }

    @Override
    public String toString() {
        return toMiniString();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj != null && obj.getClass() == getClass()) {
            AbstractBinaryOperation tmp = (AbstractBinaryOperation) obj;
            return firstExpression.equals(tmp.firstExpression)
                    && secondExpression.equals(tmp.secondExpression);
        }
        return false;
    }

    @Override
    public E evaluate(int x, int y, int z) {
        return oper(firstExpression.evaluate(x, y, z), secondExpression.evaluate(x, y, z));
    }

    @Override
    public int hashCode() {
        return 57 * firstExpression.hashCode() + 57 * 57 * secondExpression.hashCode() + getClass().hashCode();
    }
}