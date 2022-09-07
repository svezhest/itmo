package expression;

public class Negate extends AbstractUnaryOperation {
    public Negate(CommonExpression expression) {
        super(expression);
    }

    @Override
    public int getLevel() {
        return 3;
    }

    @Override
    public int function(int a) {
        return -a;
    }

    @Override
    public String getSymbol() {
        return "-";
    }
}