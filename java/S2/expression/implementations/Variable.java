package expression.implementations;

import expression.CommonExpression;
import expression.calculators.Calculator;

import java.util.List;
import java.util.Map;

public class Variable<E extends Number> implements CommonExpression<E> {
    private String var;
    private Calculator<E> calculator;
    static final Map<String, Integer> VARIABLES = Map.of(
            "x", 0,
            "y", 1,
            "z", 2
    );

    public Variable(String var, Calculator<E> calculator) {
        this.var = var;
        this.calculator = calculator;
    }

    @Override
    public int getLevel() {
        return 3;
    }

    @Override
    public String getSymbol() {
        return var;
    }

    @Override
    public String toMiniString() {
        return getSymbol();
    }

    @Override
    public String toString() {
        return toMiniString();
    }

    public boolean equals(Object obj) {
        if (obj != null && obj.getClass() == getClass()) {
            return var.equals(((Variable) obj).var);
        }
        return false;
    }

    public int hashCode() {
        return var.hashCode() * 313;
    }

    @Override
    public E evaluate(int x, int y, int z) {
        return calculator.parse(List.of(x, y, z).get(VARIABLES.get(var)).toString());
    }
}