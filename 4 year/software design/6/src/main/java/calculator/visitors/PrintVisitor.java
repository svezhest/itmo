package calculator.visitors;

import calculator.tokens.Brace;
import calculator.tokens.NumberToken;
import calculator.tokens.Operation;
import calculator.tokens.Token;

import java.io.IOException;
import java.io.OutputStream;
import java.util.List;

public class PrintVisitor implements TokenVisitor {
    private final OutputStream outputStream;
    private boolean verbose;

    public PrintVisitor(OutputStream outputStream) {
        this.outputStream = outputStream;
    }

    public void print(List<Token> tokens) {
        print(tokens, false);
    }

    public void print(List<Token> tokens, boolean verbose) {
        this.verbose = verbose;
        tokens.forEach(token -> token.accept(this));
        write("\n");
    }

    private String tokenToString(Token token) {
        String string;
        if (verbose) {
            string = token.toVerboseString() + " ";
        } else {
            string = token + " ";
        }
        return string;
    }

    private void write(String string) {
        try {
            outputStream.write(string.getBytes());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void visit(NumberToken token) {
        write(tokenToString(token));
    }

    @Override
    public void visit(Brace token) {
        write(tokenToString(token));
    }

    @Override
    public void visit(Operation token) {
        write(tokenToString(token));
    }
}
