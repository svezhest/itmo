package calculator.visitors;

import calculator.tokens.NumberToken;
import calculator.tokens.Brace;
import calculator.tokens.Operation;

public interface TokenVisitor {
    void visit(NumberToken token);
    void visit(Brace token);
    void visit(Operation token);
}
