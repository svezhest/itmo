package expression;

public interface BinaryFunction {
    String getSymbol();
    int oper(int first, int second);
    boolean isAssociative();
}