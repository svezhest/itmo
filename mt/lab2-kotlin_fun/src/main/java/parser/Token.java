package parser;

import java.text.ParseException;

public enum Token {
    N, T, FUN, LPAREN, RPAREN, COLON, COMMA, LGEN, RGEN, END;

    public static String getToken(Token token) {
        switch (token) {
            case N -> {
                return "N";
            }
            case T -> {
                return "T";
            }
            case FUN -> {
                return "fun ";
            }
            case LPAREN -> {
                return "(";
            }
            case RPAREN -> {
                return ")";
            }
            case LGEN -> {
                return "<";
            }
            case RGEN -> {
                return ">";
            }
            case COLON -> {
                return ": ";
            }
            case COMMA -> {
                return ", ";
            }
            default -> {
                return "";
            }
        }
    }
}

