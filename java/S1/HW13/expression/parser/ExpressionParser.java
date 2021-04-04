package expression.parser;

import expression.*;
import expression.exceptions.ArithmeticException;
import expression.exceptions.NoParenthesisException;
import expression.exceptions.SyntaxException;

public class ExpressionParser implements Parser {
    private String expression;
    private int pos;
    private char ch;
    private String currentOp;

    private String getContext() {
        StringBuilder context = new StringBuilder();
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

    public static void main(String[] args) throws SyntaxException {
        System.out.println(new ExpressionParser().parse("3 ** (4 ** 8)").evaluate(0, 0, 0));
    }

    private final CommonExpression[] operations = {
            new Pow(null, null),
            new Log(null, null),
            new CheckedMultiply(null, null),
            new CheckedDivide(null, null),
            new CheckedAdd(null, null),
            new CheckedSubtract(null, null)};

    private void nextChar() {
        ch = pos < this.expression.length() ? expression.charAt(pos++) : '\0';
    }

    private void skipWhitespace() {
        while (Character.isWhitespace(ch)) {
            nextChar();
        }
    }

    private boolean compareLevel(int previousLevel, String op) throws SyntaxException {
        if (op.equals("")) {
            return ch == ')' || ch == '\0';
        }
        return getLevel(op) <= previousLevel;
    }

    @Override
    public CommonExpression parse(String expression) throws SyntaxException {
        this.expression = expression;
        pos = 0;
        nextChar();
        CommonExpression ans = parse(0);
        if (ch != '\0') {
            throw new NoParenthesisException("Missing \"(\" (pos: " + pos + ")");
        }
        return ans;
    }

    private CommonExpression parse(int previousLevel) throws SyntaxException {
        CommonExpression temp = parseValue();
        skipWhitespace();
        currentOp = parseMathOperation();
        while (!compareLevel(previousLevel, currentOp)) {
            temp = createFunction(currentOp, temp, parse(getLevel(currentOp)));
        }
        return temp;
    }

    private CommonExpression parseValue() throws SyntaxException {
        skipWhitespace();
        if (ch == '-') {
            nextChar();
            if ('0' <= ch && ch <= '9') {
                return parseNumber(true);
            } else {
                return new CheckedNegate(parseValue());
            }
        } else if ('0' <= ch && ch <= '9') {
            return parseNumber(false);
        } else if (ch == 'x' || ch == 'y' || ch == 'z') {
            String s = Character.toString(ch);
            nextChar();
            skipWhitespace();
            return (new Variable(s));
        } else if (ch == '(') {
            nextChar();
            CommonExpression temp = parse(0);
            if (ch != ')') {
                throw new NoParenthesisException("Missing \")\" (pos: " + pos + ")");
            }
            nextChar();
            return temp;
        }
        throw new SyntaxException("Cannot resolve, bad syntax (pos: " + pos + ", context: '" + getContext() + "')");
    }

    private CommonExpression parseNumber(boolean isNegative) {
        StringBuilder sb = new StringBuilder();
        if (isNegative) {
            sb.append("-");
        }
        while ('0' <= ch && ch <= '9') {
            sb.append(ch);
            nextChar();
        }
        try {
            skipWhitespace();
            return new Const(Integer.parseInt(sb.toString()));
        } catch (NumberFormatException e) {
            throw new ArithmeticException("Wrong number (pos: " + pos + ", number: " + sb.toString() + ")");
        }
    }

    private String parseMathOperation() {
        StringBuilder sb = new StringBuilder();
        boolean found = true;
        boolean match;
        while (found) {
            sb.append(ch);
            found = false;
            for (CommonExpression op : operations) {
                String t = op.getSymbol();
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

    private int getLevel(String operation) throws SyntaxException {
        return createFunction(operation, null, null).getLevel();
    }

    private CommonExpression createFunction(String operation, CommonExpression a, CommonExpression b) throws SyntaxException {
        switch (operation) {
            case "**":
                return new Pow(a, b);
            case "//":
                return new Log(a, b);
            case "*":
                return new CheckedMultiply(a, b);
            case "/":
                return new CheckedDivide(a, b);
            case "+":
                return new CheckedAdd(a, b);
            case "-":
                return new CheckedSubtract(a, b);
        }
        throw new SyntaxException("Cannot find math symbol (pos: " + pos + ", context: '" + getContext() + "')");
    }
}


