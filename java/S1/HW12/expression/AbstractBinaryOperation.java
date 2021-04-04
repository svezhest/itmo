package expression;

public abstract class AbstractBinaryOperation implements CommonExpression, BinaryFunction {
    protected CommonExpression firstExpression;
    protected CommonExpression secondExpression;

    public AbstractBinaryOperation(CommonExpression firstExpression, CommonExpression secondExpression) {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
    }

    @Override
    public String toMiniString() {
        StringBuilder into = new StringBuilder();
        toMiniString(into);
        return into.toString();
    }


    public void toMiniString(StringBuilder into) {
        bracketsCheck(into, firstExpression, false);
        into.append(" ");
        into.append(getSymbol());
        into.append(" ");
        bracketsCheck(into, secondExpression, true);
    }

    private void bracketsCheck(StringBuilder into, CommonExpression exp, boolean isSecond) {
        String end = "";
        if (getLevel() > exp.getLevel()
                || (getOrder() && getLevel() == exp.getLevel() && isSecond))  {
            into.append('(');
            end = ")";
        }
        into.append(exp.toMiniString());
        into.append(end);
    }

    @Override
    public String toString() {
        StringBuilder into = new StringBuilder();
        into.append('(');
        into.append(firstExpression.toString());
        into.append(" ");
        into.append(getSymbol());
        into.append(" ");
        into.append(secondExpression.toString());
        into.append(')');
        return into.toString();
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
    public int evaluate(int x) {
        return function(firstExpression.evaluate(x), secondExpression.evaluate(x));
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return function(firstExpression.evaluate(x, y, z), secondExpression.evaluate(x, y, z));
    }

    @Override
    public int hashCode() {
        return 57 * firstExpression.hashCode() + 57 * 57 * secondExpression.hashCode() + getClass().hashCode();
    }
}