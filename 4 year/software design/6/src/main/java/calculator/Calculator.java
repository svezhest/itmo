package calculator;

import calculator.tokenizers.Tokenizer;
import calculator.tokens.Token;
import calculator.visitors.CalcVisitor;
import calculator.visitors.ParserVisitor;
import calculator.visitors.PrintVisitor;

import java.io.ByteArrayInputStream;
import java.nio.charset.StandardCharsets;
import java.util.List;

public class Calculator {
    public static int calculate(String s, boolean print) {
        Tokenizer tokenizer = new Tokenizer();
        List<Token> tokens = tokenizer.tokenize(new ByteArrayInputStream(s.getBytes(StandardCharsets.UTF_8)));
        PrintVisitor printVisitor = new PrintVisitor(System.out);
        if (print) {
            printVisitor.print(tokens, true);
        }
        ParserVisitor parserVisitor = new ParserVisitor();
        List<Token> expression = parserVisitor.parse(tokens);
        if (print) {
            printVisitor.print(expression, true);
            printVisitor.print(expression);
        }
        CalcVisitor calcVisitor = new CalcVisitor();
        List<Token> result = calcVisitor.calculate(expression);
        return Integer.parseInt(result.get(0).toString());
    }
}
