package calculator.visitors;

import calculator.tokens.Brace;
import calculator.tokens.NumberToken;
import calculator.tokens.Operation;
import calculator.tokens.Token;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class ParserVisitor implements TokenVisitor {
    private List<Token> result;
    private Stack<Token> stack;
    private enum State {
        NUMBER, OPERATION, RIGHT, LEFT, NONE
    }
    private State state;

    @Override
    public void visit(NumberToken token) {
        if (state == State.NUMBER) {
            throw new RuntimeException("Parsing error: two numbers in line (missing operation)");
        }
        if (state == State.RIGHT) {
            throw new RuntimeException("Parsing error: right brace and then number");
        }
        state = State.NUMBER;
        result.add(token);
    }

    @Override
    public void visit(Brace token) {
        if (token == Brace.LEFT) {
            if (state == State.NUMBER) {
                throw new RuntimeException("Parsing error: number and then left brace");
            }
            if (state == State.RIGHT) {
                throw new RuntimeException("Parsing error: right and then left braces (missing operation)");
            }
            state = State.LEFT;
            stack.push(token);
        } else {
            if (state == State.OPERATION) {
                throw new RuntimeException("Parsing error: operation and then right brace");
            }
            if (state == State.LEFT) {
//                is not allowed because of "2 + (()) + 2"
                throw new RuntimeException("Parsing error: left and then right braces (missing expression)");
            }
            state = State.RIGHT;
            if (stack.isEmpty()) {
                throw new RuntimeException("Parsing error: unmatched right brace");
            }
            while (!stack.isEmpty()) {
                Token prev = stack.peek();
                stack.pop();
                if (prev instanceof Operation) {
                    result.add(prev);
                } else {
                    return;
                }
            }
            throw new RuntimeException("Parsing error: unmatched right brace");
        }
    }

    @Override
    public void visit(Operation token) {
        if (state == State.OPERATION) {
            throw new RuntimeException("Parsing error: two operations in line");
        }
        if (state == State.LEFT) {
            throw new RuntimeException("Parsing error: left brace and then operation");
        }
        state = State.OPERATION;
        while (!stack.isEmpty()) {
            Token prev = stack.peek();
            if ((prev instanceof Operation) && ((Operation) prev).getPriority() >= token.getPriority()) {
                result.add(prev);
                stack.pop();
            } else {
                break;
            }
        }
        stack.push(token);
    }

    public List<Token> parse(List<Token> tokens) {
        result = new ArrayList<>();
        stack = new Stack<>();
        state = State.NONE;

        for (Token token : tokens) {
            token.accept(this);
        }

        while (!stack.isEmpty()) {
            Token token = stack.peek();
            stack.pop();
            if (token instanceof Brace) {
                throw new RuntimeException("Parsing error: unmatched left brace");
            }
            result.add(token);
        }
        return result;
    }
}
