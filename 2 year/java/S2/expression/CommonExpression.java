package expression;

public interface CommonExpression<E extends Number> extends GenericTripleExpression<E> {
    int getLevel();
    String getSymbol();
}