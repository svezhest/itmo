package calculator.tokens;

import calculator.visitors.TokenVisitor;

public enum Operation implements Token {
    PLUS, MINUS, MUL, DIV;

    @Override
    public void accept(TokenVisitor visitor) {
        visitor.visit(this);
    }

    public int getPriority() {
        switch (this) {
            case PLUS, MINUS -> {
                return 1;
            }
            case MUL, DIV -> {
                return 2;
            }
        }
        return -1;
    }

    @Override
    public String toString() {
        switch (this) {
            case PLUS -> {
                return "+";
            }
            case MINUS -> {
                return "-";
            }
            case MUL -> {
                return "*";
            }
            case DIV -> {
                return "/";
            }
        }
        return null;
    }

    @Override
    public String toVerboseString() {
        return super.toString();
    }
}
