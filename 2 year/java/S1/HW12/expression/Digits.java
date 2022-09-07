package expression;


public class Digits extends AbstractUnaryOperation {
    public Digits(CommonExpression expression) {
        super(expression);
    }

    @Override
    public int getLevel() {
        return 3;
    }

    @Override
    public int function(int i) {
        long abs = Long.max(i, -((long) i));
        long sum = 0;
        while (abs > 0) {
            sum += abs % 10;
            abs = abs / 10;
        }
        int res = (int) sum;
        return res;
    }

    @Override
    public String getSymbol() {
        return "digits";
    }
}