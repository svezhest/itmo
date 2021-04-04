package expression;

public interface BinaryFunction {
    String getSymbol();
    int function(int first, int second);
    boolean getOrder();
}