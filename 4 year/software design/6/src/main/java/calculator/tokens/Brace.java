package calculator.tokens;

import calculator.visitors.TokenVisitor;

public enum Brace implements Token {
    LEFT, RIGHT;

    @Override
    public void accept(TokenVisitor visitor) {
        visitor.visit(this);
    }

    @Override
    public String toString() {
        switch (this) {
            case LEFT -> {
                return "(";
            }
            case RIGHT -> {
                return ")";
            }
        }
        return null;
    }

    @Override
    public String toVerboseString() {
        return super.toString();
    }
}
