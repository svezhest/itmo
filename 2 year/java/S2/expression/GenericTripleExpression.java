package expression;

public interface GenericTripleExpression<E extends Number> extends ToMiniString {
        E evaluate(int x, int y, int z);
    }