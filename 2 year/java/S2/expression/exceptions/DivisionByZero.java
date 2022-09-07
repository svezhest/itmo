package expression.exceptions;

public class DivisionByZero extends ArithmeticException {
    public DivisionByZero(final String message) {
        super(message);
    }
}
