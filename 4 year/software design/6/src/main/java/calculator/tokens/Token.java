package calculator.tokens;

import calculator.visitors.TokenVisitor;

public interface Token {
    void accept(TokenVisitor visitor);

    String toString();

    String toVerboseString();
}
