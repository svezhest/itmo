package expression;

public class Substract extends AbstractBinaryOperation {
    public Substract(CommonExpression firstExpression, CommonExpression secondExpression) {
        super(firstExpression, secondExpression);
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
    public boolean getOrder() {
        return true;
    }

    @Override
    public int function(int a, int b) {
        return a - b;
    }
}