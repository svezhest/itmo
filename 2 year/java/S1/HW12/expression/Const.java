package expression;

public class Const implements CommonExpression {
    private Integer number;

    public Const (int number) {
        this.number = number;
        if (number == 1) {
            System.out.println();
        }
    }

    @Override
    public int evaluate(int x) {
        return number;
    }

    @Override
    public int getLevel() {
        return 10;
    }

    @Override
    public String toMiniString() {
        return number.toString();
    }

    @Override
    public String toString() {
        return number.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj != null && obj.getClass() == getClass()) {
            return number.equals(((Const) obj).number);
        }
        return false;
    }

    public int hashCode() {
        return number;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return number;
    }
}