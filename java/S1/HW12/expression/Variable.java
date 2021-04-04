package expression;

import java.util.List;
import java.util.Map;

public class Variable implements CommonExpression {
    private String var;
    static final Map<String, Integer> VARIABLES = Map.of(
            "x", 0,
            "y", 1,
            "z", 2
    );

    public Variable(String var) {
        this.var = var;
    }

    @Override
    public int evaluate(int x) {
        return x;
    }

    @Override
    public int getLevel() {
        return 3;
    }

    @Override
    public String toMiniString() {
        return var;
    }

    @Override
    public String toString() {
        return var;
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
    public int evaluate(int x, int y, int z) {
        return List.of(x, y, z).get(VARIABLES.get(var));
    }
}