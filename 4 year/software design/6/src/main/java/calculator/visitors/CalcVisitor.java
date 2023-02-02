package calculator.visitors;

import calculator.tokens.Brace;
import calculator.tokens.NumberToken;
import calculator.tokens.Operation;
import calculator.tokens.Token;

import java.util.List;
import java.util.Stack;

public class CalcVisitor implements TokenVisitor {
    private Stack<Token> stack;

    @Override
    public void visit(NumberToken token) {
        stack.add(token);
    }

    @Override
    public void visit(Brace token) {
        throw new RuntimeException("Calc error: no braces expected in reverse polish notation");
    }

    @Override
    public void visit(Operation token) {
        int a = Integer.parseInt(stack.peek().toString());
        stack.pop();
        int b = Integer.parseInt(stack.peek().toString());
        stack.pop();
        switch (token) {
            case PLUS -> stack.push(new NumberToken(b + a));
            case MINUS -> stack.push(new NumberToken(b - a));
            case MUL -> stack.push(new NumberToken(b * a));
            case DIV -> stack.push(new NumberToken(b / a));
        }
    }

    public List<Token> calculate(List<Token> tokens) {
        stack = new Stack<>();
        for (Token token : tokens) {
            token.accept(this);
        }
        return stack;
    }
}
