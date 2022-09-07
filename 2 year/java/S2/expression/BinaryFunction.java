package expression;

public interface BinaryFunction<E extends Number> {
    String getSymbol();
    E oper(E first, E second);
    boolean isAssociative();
}