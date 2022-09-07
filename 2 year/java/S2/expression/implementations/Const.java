package expression.implementations;

import expression.CommonExpression;

public class Const<E extends Number> implements CommonExpression<E> {
    private E number;

    public Const (E number) {
        this.number = number;
    }

    @Override
    public int getLevel() {
        return 10;
    }

    @Override
    public String getSymbol() {return number.toString(); }

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
        return number.hashCode();
    }

    @Override
    public E evaluate(int x, int y, int z) {
        return number;
    }
}