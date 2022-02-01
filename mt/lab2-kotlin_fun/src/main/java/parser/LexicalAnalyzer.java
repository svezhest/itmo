package parser;

import java.io.IOException;
import java.io.InputStream;
import java.text.ParseException;

class LexicalAnalyzer {
    InputStream is;
    int curChar;
    int curPos;
    Token curToken;

    public LexicalAnalyzer(InputStream is) throws ParseException {
        this.is = is;
        curPos = 0;
        nextChar();
    }

    private boolean isBlank(int c) {
        return c == ' ' || c == '\r' || c == '\n' || c == '\t';
    }

    private boolean isLowercase(int c) {
        return Character.isLowerCase(c);
    }

    private boolean isUppercase(int c) {
        return Character.isUpperCase(c);
    }

    private boolean isLetterOrDigitOrSym(int c) {
        return Character.isLetterOrDigit(c) || c == '_';
    }

    private void nextChar() throws ParseException {
        curPos++;
        try {
            curChar = is.read();
        } catch (IOException e) {
            throw new ParseException(e.getMessage(), curPos);
        }
    }

    public void nextToken() throws ParseException {
        while (isBlank(curChar)) {
            nextChar();
        }

        switch (curChar) {
            case 'f':
                nextChar();
                if (curChar == 'u') {
                    nextChar();
                    if (curChar == 'n') {
                        nextChar();
                        if (isBlank(curChar) || curChar == -1) {
                            curToken = Token.FUN;
                            nextChar();
                            return;
                        } else if (!isLetterOrDigitOrSym(curChar)) {
                            throw new ParseException("Wrong 'fun' keyword placement at " + curPos, curPos);
                        }
                    }
                }
                while (isLetterOrDigitOrSym(curChar)) {
                    nextChar();
                }
                curToken = Token.N;
                return;
            case '(':
                curToken = Token.LPAREN;
                nextChar();
                return;
            case ')':
                curToken = Token.RPAREN;
                nextChar();
                return;
            case '<':
                curToken = Token.LGEN;
                nextChar();
                return;
            case '>':
                curToken = Token.RGEN;
                nextChar();
                return;
            case ':':
                curToken = Token.COLON;
                nextChar();
                return;
            case ',':
                curToken = Token.COMMA;
                nextChar();
                return;
            case -1:
                curToken = Token.END;
                nextChar();
                return;
        }

        if (isLowercase(curChar)) {
            nextChar();
            while (isLetterOrDigitOrSym(curChar)) {
                nextChar();
            }
            curToken = Token.N;
            return;
        } else if (isUppercase(curChar)) {
            nextChar();
            while (isLetterOrDigitOrSym(curChar)) {
                nextChar();
            }
            curToken = Token.T;
            return;
        } else {
            throw new ParseException("Illegal character \'" + (char)curChar + "\' at " + curPos, curPos);
        }
    }

    public Token curToken() {
        return curToken;
    }

    public int curPos() {
        return curPos;
    }

}