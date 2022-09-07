package expression;

public class ShiftLeft extends AbstractBinaryOperation {
    public ShiftLeft(CommonExpression firstExpression, CommonExpression secondExpression) {
        super(firstExpression, secondExpression);
    }

    @Override
    public int getLevel() {
        return 0;
    }

    @Override
    public String getSymbol() {
        return "<<";
    }

    @Override
    public boolean getOrder() {
        return true;
    }

    @Override
    public int function(int first, int second) {
        return first << second;
    }
}