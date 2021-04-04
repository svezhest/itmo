package expression;

public class Multiply extends AbstractBinaryOperation {
    public Multiply(CommonExpression firstExpression, CommonExpression secondExpression) {
        super(firstExpression, secondExpression);
    }

    @Override
    public int getLevel() {
        return 2;
    }

    @Override
    public String getSymbol() {
        return "*";
    }

    @Override
    public boolean getOrder() {
        return false;
    }

    @Override
    public int function(int a, int b) {
        return a * b;
    }
}