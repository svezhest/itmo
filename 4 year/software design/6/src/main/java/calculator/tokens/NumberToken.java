package calculator.tokens;

import calculator.visitors.TokenVisitor;

public class NumberToken implements Token {
    private final int value;

    public NumberToken(int value) {
        this.value = value;
    }

    @Override
    public void accept(TokenVisitor visitor) {
        visitor.visit(this);
    }

    @Override
    public String toString() {
        return String.valueOf(value);
    }

    @Override
    public String toVerboseString() {
        return "NUMBER(" + value + ")";
    }
}
