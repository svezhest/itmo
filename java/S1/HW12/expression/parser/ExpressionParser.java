package expression.parser;

import expression.*;

import java.util.Map;
import java.util.Objects;

public class ExpressionParser extends BaseParser implements Parser {
    private final int bracketLevel = -1;

    private final Map<Character, String> oneVar = Map.of(
            'd', "igits",
            'r', "everse"
    );

    private final Map<Character, String> secondPart = Map.of(
            '*', "",
            '-', "",
            '+', "",
            '/', "",
            '>', ">",
            '<', "<"
    );

    private int getLevel(char c) {
        return Objects.requireNonNull(createTwoVar(c, null, null)).getLevel();
    }

    private AbstractUnaryOperation createOneVar(char c, CommonExpression expression) {
        switch (c) {
            case 'd':
                return new Digits(expression);
            case 'r':
                return new Reverse(expression);
            default:
                return null;
        }
    }

    private AbstractBinaryOperation createTwoVar(char c, CommonExpression firstExpression, CommonExpression secondExpression) {
        switch (c) {
            case '+':
                return new Add(firstExpression, secondExpression);
            case '-':
                return new Substract(firstExpression, secondExpression);
            case '*':
                return new Multiply(firstExpression, secondExpression);
            case '/':
                return new Divide(firstExpression, secondExpression);
            case '>':
                return new ShiftRight(firstExpression, secondExpression);
            case '<':
                return new ShiftLeft(firstExpression, secondExpression);
            default:
                return null;
        }
    }

    @Override
    public CommonExpression parse(String expression) {
        newSource(new StringSource(expression));
        nextChar();
        CommonExpression ans = parse(bracketLevel);
        if (ch != '\0') {
            throw error("waste \")\"");
        }
        return ans;
    }

    public void nextChar() {
        do {
            super.nextChar();
        } while (Character.isWhitespace(ch));
    }

    private CommonExpression parse(int previousLevel) {
        CommonExpression temp = parseValue();
        while (!testSymbol(previousLevel)) {
            temp = parseSymbol(temp);
        }
        return temp;
    }

    private boolean testSymbol(int previousLevel) {
        if (!secondPart.containsKey(ch)) {
            return ch == ')' || ch == '\0';
        }
        return (getLevel(ch) <= previousLevel);
    }


    private CommonExpression parseValue() {
        if (test('-')) {
            if (between('0', '9')) {
                return parseNumber(true);
            } else {
                return new Negate(parseValue());
            }
        } else if (between('0', '9')) {
            return parseNumber(false);
        } else if (between('x', 'z')) {
            String s = Character.toString(ch);
            nextChar();
            return (new Variable(s));
        } else if (test('(')) {
            CommonExpression temp = parse(bracketLevel);
            if (ch == '\0') {
                throw error("Missed \")\"");
            }
            nextChar();
            return temp;
        } else if (oneVar.containsKey(ch)) {
            for (Map.Entry<Character, String> temp : oneVar.entrySet()) {
                if (test(temp.getKey())) {
                    expect(temp.getValue());
                    return createOneVar(temp.getKey(), parseValue());
                }
            }
        }
        throw error("No Value (bracket, number or variable)");
    }

    private CommonExpression parseNumber(boolean isMinus) {
        StringBuilder numb = new StringBuilder();
        if (isMinus) {
            numb.append("-");
        }
        while (between('0', '9')) {
            numb.append(ch);
            super.nextChar();
        }
        try {
            if (Character.isWhitespace(ch)) {
                nextChar();
            }
            return new Const(Integer.parseInt(numb.toString()));
        } catch (NumberFormatException e) {
            throw error("Illegal number " + e);
        }
    }

    private CommonExpression parseSymbol(CommonExpression past) {
        for (Map.Entry<Character, String> temp : secondPart.entrySet()) {
            if (test(temp.getKey())) {
                expect(temp.getValue());
                return createTwoVar(temp.getKey(), past, parse(getLevel(temp.getKey())));
            }
        }
        throw error("Expected Math sign");
    }
}