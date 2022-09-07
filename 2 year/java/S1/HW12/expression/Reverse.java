package expression;

public class Reverse extends AbstractUnaryOperation {
    public Reverse(CommonExpression expression) {
        super(expression);
    }

    @Override
    public int getLevel() {
        return 3;
    }

    @Override
    public int function(int i) {
        int c = 1;
        if (i < 0) {
            c = -1;
        }
        long result = 0;
        long abs = Long.max(i, -((long) i));
        while (abs > 0) {
            result = result * 10 + abs % 10;
            abs /= 10;
        }
        return (int) result * c;
    }

    @Override
    public String getSymbol() {
        return "reverse";
    }
}