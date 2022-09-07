package expression.parser;

import expression.TripleExpression;
import expression.exceptions.ArithmeticException;
import expression.exceptions.SyntaxException;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public interface Parser {
    TripleExpression parse(String expression) throws ArithmeticException, SyntaxException;
}
