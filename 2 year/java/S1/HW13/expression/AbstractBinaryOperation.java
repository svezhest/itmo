package expression;

public abstract class AbstractBinaryOperation implements CommonExpression, BinaryFunction {
    private CommonExpression firstExpression;
    private CommonExpression secondExpression;

    public AbstractBinaryOperation(CommonExpression firstExpression, CommonExpression secondExpression) {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
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
                || (isAssociative() && getLevel() == exp.getLevel() && isSecond))  {
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
    public int evaluate(int x, int y, int z) {
        return oper(firstExpression.evaluate(x, y, z), secondExpression.evaluate(x, y, z));
    }

    @Override
    public int hashCode() {
        return 57 * firstExpression.hashCode() + 57 * 57 * secondExpression.hashCode() + getClass().hashCode();
    }
}