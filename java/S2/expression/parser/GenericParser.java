package expression.parser;

import expression.CommonExpression;
import expression.exceptions.ArithmeticException;
import expression.exceptions.SyntaxException;

public interface GenericParser<E extends Number> {
    CommonExpression<E> parse(String expression) throws ArithmeticException, SyntaxException;
}
