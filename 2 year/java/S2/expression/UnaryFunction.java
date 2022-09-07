package expression;

public interface UnaryFunction<E extends Number> {
    E function(E x);
    String getSymbol();
}