package parser;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.text.ParseException;

import static org.junit.jupiter.api.Assertions.*;

class ParserTest {
    private String lexString(String s) throws ParseException {
        InputStream stream = new ByteArrayInputStream(s.getBytes(StandardCharsets.UTF_8));
        LexicalAnalyzer lexer = new LexicalAnalyzer(stream);
        StringBuilder stringBuilder = new StringBuilder();
        while (true) {
            lexer.nextToken();
            Token token = lexer.curToken;
            stringBuilder.append(Token.getToken(token));
            if (token == Token.END) {
                break;
            }
        }
        return stringBuilder.toString();
    }

    private Parser.Node parseString(String s) throws ParseException {
        InputStream stream = new ByteArrayInputStream(s.getBytes(StandardCharsets.UTF_8));
        LexicalAnalyzer lexer = new LexicalAnalyzer(stream);
        return new Parser(lexer).run();
    }

//    Some quick tests
    @Test
    public void simpleLexer() {
        try {
            String s = "fun abacaba(a: Int) : Void";
            Assertions.assertEquals(lexString(s), "fun N(N: T): T");
        } catch (ParseException e) {
            Assertions.fail();
        }

        try {
            String s = "fun wee____wee(iushfdsuSDFDSw_fds: Int, b1__wd :    Unit) : Int";
            Assertions.assertEquals(lexString(s), "fun N(N: T, N: T): T");
        } catch (ParseException e) {
            Assertions.fail();
        }

        try {
            String s = "fun pupalupa() : String";
            Assertions.assertEquals(lexString(s), "fun N(): T");
        } catch (ParseException e) {
            Assertions.fail();
        }

//        no extra space
        try {
            String s = "fun pupalupa():String";
            Assertions.assertEquals(lexString(s), "fun N(): T");
        } catch (ParseException e) {
            Assertions.fail();
        }

//        a lot of spaces
        try {
            String s = "fun     pupalupa   (  )       :               String               ";
            Assertions.assertEquals(lexString(s), "fun N(): T");
        } catch (ParseException e) {
            Assertions.fail();
        }
    }

//    There are some cases with impossible tokens
    @Test
    public void evenLexerThrows() {
        assertThrows(ParseException.class, () -> {
            String s = "1 + 2 = 4";
            lexString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "^^^^";
            lexString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "that_looks_like_a_n&me_but_it_is_not";
            lexString(s);
        });

//        keyword fun should be followed by whitespace
        assertThrows(ParseException.class, () -> {
            String s = "fun!";
            lexString(s);
        });

//        no dashes
        assertThrows(ParseException.class, () -> {
            String s = "fun-fun";
            lexString(s);
        });
    }

    @Test
    public void misc() {
        try {
//            this is clearly a fun token
            String s = "fun";
            Assertions.assertEquals(lexString(s), "fun ");
        } catch (ParseException e) {
            Assertions.fail();
        }

        try {
//            brackets parsing test
            String s = "((())(()()()()()()()))())(())))))";
            Assertions.assertEquals(lexString(s), "((())(()()()()()()()))())(())))))");
        } catch (ParseException e) {
            Assertions.fail();
        }
    }

//    big test to see if the parser allows bad declarations
    @Test
    public void badDeclarations() {
        assertThrows(ParseException.class, () -> {
            String s = "fun (a: Int) : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fan what(a: Int) : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fun 99(a: Int) : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fun sdf : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fun kek(a: Int), Void";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fun kek(a: Int) Void";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fun kek(a: Int) : ";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fun gggghhh(a: Int) :: Irrr";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fun fun(a: Int) : Irrr";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "function fsdfun(a: Int) : Irrr";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "def osdfj(a: Int) : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "abc(a: Int) : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "ffun abc(a: Int) : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fuun abc(a: Int) : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "funn abc(a: Int) : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "f u n abc(a: Int) : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fun dot com(a: Int) : Int";
            parseString(s);
        });

//        no tricks
        assertThrows(ParseException.class, () -> {
            String s = "fun dotcom(fun: Int) : Int";
            parseString(s);
        });
    }

    @Test
    public void unluckyTest() {
        assertThrows(ParseException.class, () -> {
            String s = "fun abs(a: Int,) : Int";
            parseString(s);
        });
    }

    @Test
    public void lexedModTest() {
        try {
            String s = "fun abacaba(a: Int<Int>) : Void";
            Assertions.assertEquals(lexString(s), "fun N(N: T<T>): T");
        } catch (ParseException e) {
            Assertions.fail();
        }


        try {
            String s = "fun abacaba(a: Int<List<Int, Bool>>) : Void";
            Assertions.assertEquals(lexString(s), "fun N(N: T<T<T, T>>): T");
        } catch (ParseException e) {
            Assertions.fail();
        }
    }

    @Test
    public void goodGenerics() {
        assertDoesNotThrow(() -> {
            String s = "fun s(a: Int<>) : Int";
            parseString(s);
        });

        assertDoesNotThrow(() -> {
            String s = "fun s(a: Int<Int>) : Int";
            parseString(s);
        });

        assertDoesNotThrow(() -> {
            String s = "fun s(a: Int<A>) : Int<L>";
            parseString(s);
        });

        assertDoesNotThrow(() -> {
            String s = "fun s(a: Int<K<F>>) : Int<L, M>";
            parseString(s);
        });
    }

    @Test
    public void badGenerics() {
        assertThrows(ParseException.class, () -> {
            String s = "fun a(a: Int<1>) : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fun a(a: Int<A, >) : Int";
            parseString(s);
        });


        assertThrows(ParseException.class, () -> {
            String s = "fun a(a: Int<a : Int>) : Int";
            parseString(s);
        });

//        not a type
        assertThrows(ParseException.class, () -> {
            String s = "fun a(a: Int<a>) : Int";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "<fun a(a: Int<Int>) : Int>";
            parseString(s);
        });

        assertThrows(ParseException.class, () -> {
            String s = "fun a(a: Int<<>>) : Int";
            parseString(s);
        });
    }
}