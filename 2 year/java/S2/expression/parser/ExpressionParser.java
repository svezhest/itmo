package expression.parser;

import expression.CommonExpression;
import expression.calculators.Calculator;
import expression.exceptions.ArithmeticException;
import expression.exceptions.NoParenthesisException;
import expression.exceptions.SyntaxException;
import expression.implementations.*;

public class ExpressionParser<E extends Number> implements GenericParser<E> {
    private final CommonExpression<?>[] operations = {
            new CheckedMultiply<>(null, null, null),
            new CheckedDivide<>(null, null, null),
            new CheckedAdd<>(null, null, null),
            new CheckedSubtract<>(null, null, null),
            new Min<>(null, null, null),
            new Max<>(null, null, null),
            new Count<>(null, null)

    };
    private String expression;
    private int pos;
    private char ch;
    private String currentOp;
    private final Calculator<E> calculator;

    public ExpressionParser(final Calculator<E> calculator) {
        this.calculator = calculator;
    }

    private String getContext() {
        final StringBuilder context = new StringBuilder();
        if (pos > 0) {
            context.append(expression.charAt(pos - 1));
        }
        if (pos < expression.length()) {
            context.append(expression.charAt(pos));
            if (pos + 1 < expression.length()) {
                context.append(expression.charAt(pos + 1));
            }
        }
        return context.toString();
    }

    private void nextChar() {
        ch = pos < this.expression.length() ? expression.charAt(pos++) : '\0';
    }

    private void skipWhitespace() {
        while (Character.isWhitespace(ch)) {
            nextChar();
        }
    }

    private boolean compareLevel(final int previousLevel, final String op) throws SyntaxException {
        if (op.equals("")) {
            return ch == ')' || ch == '\0';
        }
        return getLevel(op) <= previousLevel;
    }

    @Override
    public CommonExpression<E> parse(final String expression) throws SyntaxException {
        this.expression = expression;
        pos = 0;
        nextChar();
        final CommonExpression<E> ans = parse(-1);
        if (ch != '\0') {
            throw new NoParenthesisException("Missing \"(\" (pos: " + pos + ")");
        }
        return ans;
    }

    private CommonExpression<E> parse(final int previousLevel) throws SyntaxException {
        CommonExpression<E> temp = parseValue();
        skipWhitespace();
        currentOp = parseOperation();
        while (!compareLevel(previousLevel, currentOp)) {
            temp = createBinaryFunction(currentOp, temp, parse(getLevel(currentOp)));
        }
        return temp;
    }

    private CommonExpression<E> parseValue() throws SyntaxException {
        skipWhitespace();
        if (ch == '-') {
            nextChar();
            if ('0' <= ch && ch <= '9') {
                return parseNumber(true);
            } else {
                return new CheckedNegate<>(parseValue(), calculator);
            }
        } else if ('0' <= ch && ch <= '9') {
            return parseNumber(false);
        } else if (ch == 'x' || ch == 'y' || ch == 'z') {
            final String s = Character.toString(ch);
            nextChar();
            skipWhitespace();
            return (new Variable<>(s, calculator));
        } else if (ch == '(') {
            nextChar();
            final CommonExpression<E> temp = parse(0);
            if (ch != ')') {
                throw new NoParenthesisException("Missing \")\" (pos: " + pos + ")");
            }
            nextChar();
            return temp;
        }
        final String operation = parseOperation();
        return createUnaryFunction(operation, parseValue());
    }

    private CommonExpression<E> parseNumber(final boolean isNegative) {
        final StringBuilder sb = new StringBuilder();
        if (isNegative) {
            sb.append("-");
        }
        while ('0' <= ch && ch <= '9') {
            sb.append(ch);
            nextChar();
        }
        try {
            skipWhitespace();
            return new Const<>(calculator.parse(sb.toString()));
        } catch (final NumberFormatException e) {
            throw new ArithmeticException("Wrong number (pos: " + pos + ", number: " + sb.toString() + ")");
        }
    }

    private String parseOperation() {
        final StringBuilder sb = new StringBuilder();
        boolean found = true;
        boolean match;
        while (found) {
            sb.append(ch);
            found = false;
            for (final CommonExpression<?> op : operations) {
                final String t = op.getSymbol();
                if (sb.length() > t.length()) {
                    continue;
                }
                match = true;
                for (int i = 0; i < sb.length(); i++) {
                    if (sb.charAt(i) != t.charAt(i)) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    found = true;
                    nextChar();
                    if (ch == '\0') {
                        return sb.toString();
                    }
                    break;
                }
            }
        }
        return sb.deleteCharAt(sb.length() - 1).toString();
    }

    private int getLevel(final String operation) throws SyntaxException {
        return createBinaryFunction(operation, null, null).getLevel();
    }

    private CommonExpression<E> createUnaryFunction(final String operation, final CommonExpression<E> a) throws SyntaxException {
        if ("count".equals(operation)) {
            return new Count<>(a, calculator);
        }
        throw new SyntaxException("Cannot find unary math symbol (pos: " + pos + ", context: '" + getContext() + "')");
    }

    private CommonExpression<E> createBinaryFunction(final String operation, final CommonExpression<E> a, final CommonExpression<E> b) throws SyntaxException {
        switch (operation) {
            case "*":
                return new CheckedMultiply<>(a, b, calculator);
            case "/":
                return new CheckedDivide<>(a, b, calculator);
            case "+":
                return new CheckedAdd<>(a, b, calculator);
            case "-":
                return new CheckedSubtract<>(a, b, calculator);
            case "min":
                return new Min<>(a, b, calculator);
            case "max":
                return new Max<>(a, b, calculator);
        }
        throw new SyntaxException("Cannot find binary math symbol (pos: " + pos + ", context: '" + getContext() + "')");
    }
}


