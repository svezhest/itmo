package calculator.tokenizers;

import calculator.tokens.Brace;
import calculator.tokens.NumberToken;
import calculator.tokens.Operation;
import calculator.tokens.Token;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

public class Tokenizer {
    private enum State {
        CHAR, NUMBER, EOF
    }
//    соответсвует START, NUMBER и EOF на картинке. для ERROR state не нужен

    private State state;
    private List<Token> tokens;
    private int currentNumber;

    private boolean handleChar(int ch) {
        switch (state) {
            case CHAR -> {
                if (Character.isDigit(ch)) {
                    state = State.NUMBER;
                    return handleChar(ch);
                } else {
                    switch (ch) {
                        case '+' -> tokens.add(Operation.PLUS);
                        case '-' -> tokens.add(Operation.MINUS);
                        case '*' -> tokens.add(Operation.MUL);
                        case '/' -> tokens.add(Operation.DIV);
                        case '(' -> tokens.add(Brace.LEFT);
                        case ')' -> tokens.add(Brace.RIGHT);
                        case -1 -> {
                            state = State.EOF;
                            return handleChar(ch);
                        }
                        default -> {
                            if (Character.isWhitespace(ch)) {
                                return false;
                            }
                            throw new RuntimeException("Illegal character");
                        }
                    }
                }
            }

            case NUMBER -> {
                if (Character.isDigit(ch)) {
                    currentNumber = currentNumber * 10 + Integer.parseInt(Character.toString(ch));
                } else {
                    tokens.add(new NumberToken(currentNumber));
                    currentNumber = 0;
                    state = State.CHAR;
                    return handleChar(ch);
                }
            }

            case EOF -> {
                return true;
            }
        }
        return false;
    }

    public List<Token> tokenize(InputStream inputStream) {
        state = State.CHAR;
        tokens = new ArrayList<>();
        boolean eof = false;

        while (!eof) {
            int ch = 0;
            try {
                ch = inputStream.read();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            eof = handleChar(ch);
        }

        return tokens;
    }
}
