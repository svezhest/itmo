import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.io.*;
import java.nio.charset.StandardCharsets;

public class TestAntlr {
    public String convert(String s) throws IOException {
        InputStream stream = new ByteArrayInputStream(s.getBytes(StandardCharsets.UTF_8));
        GrammarLexer grammarLexer = new GrammarLexer(CharStreams.fromStream(stream));
        CommonTokenStream commonTokenStream = new CommonTokenStream(grammarLexer);
        GrammarParser grammarParser = new GrammarParser(commonTokenStream);
        String res = grammarParser.tex().value;
        try {
            FileWriter myWriter = new FileWriter("answ.html");
            myWriter.write(res);
            myWriter.close();
            System.out.println("Successfully wrote to the file.");
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        return res;
    }

    @Test
    public void test1() {
        try {
            String s = "\\begin{document}\n" +
                    "    $a + b * c$\n" +
                    "\\end{document}";
            Assertions.assertEquals(convert(s), "<html> <head> <title> Tex2HTML </title> </head> <body>\n" +
                    "<math displaystyle=\"true\"> <mrow> <mrow> <mi> a </mi> <mo> + </mo> <mrow> <mi> b </mi> <mo> * </mo> <mi> c </mi> </mrow> </mrow> </mrow> </math>\n" +
                    "</body> </html>");
        } catch (Exception e) {
            Assertions.fail();
        }
    }

    @Test
    public void test2() {
        try {
            String s = "\\begin{document}\n" +
                    "    $a + 2 * 3 + b / -(2 * c)$\n" +
                    "\\end{document}";
            Assertions.assertEquals(convert(s), "<html> <head> <title> Tex2HTML </title> </head> <body>\n" +
                    "<math displaystyle=\"true\"> <mrow> <mrow> <mrow> <mi> a </mi> <mo> + </mo> <mrow> <mn> 2 </mn> <mo> * </mo> <mn> 3 </mn> </mrow> </mrow> <mo> + </mo> <mrow> <mi> b </mi> <mo> / </mo> <mo> - </mo> <mrow> <mo> ( </mo> <mrow> <mn> 2 </mn> <mo> * </mo> <mi> c </mi> </mrow> <mo> ) </mo> </mrow> </mrow> </mrow> </mrow> </math>\n" +
                    "</body> </html>");
        } catch (Exception e) {
            Assertions.fail();
        }
    }

    @Test
    public void test3() {
        try {
            String s = "\\begin{document}\n" +
                    "    $ C^{a^{b^{c - 8}}}_{1}$\n" +
                    "\\end{document}";
            Assertions.assertEquals(convert(s), "<html> <head> <title> Tex2HTML </title> </head> <body>\n" +
                    "<math displaystyle=\"true\"> <mrow> <msubsup> <mi> C </mi> <mn> 1 </mn> <msup> <mi> a </mi> <msup> <mi> b </mi> <mrow> <mi> c </mi> <mo> - </mo> <mn> 8 </mn> </mrow> </msup> </msup> </msubsup> </mrow> </math>\n" +
                    "</body> </html>");
        } catch (Exception e) {
            Assertions.fail();
        }
    }

    @Test
    public void test4() {
        try {
            String s = "\\begin{document}\n" +
                    "    $ \\frac{\\frac{1}{2}}{3}$\n" +
                    "\\end{document}";
            Assertions.assertEquals(convert(s), "<html> <head> <title> Tex2HTML </title> </head> <body>\n" +
                    "<math displaystyle=\"true\"> <mrow> <mfrac> <mrow><mfrac> <mrow><mn> 1 </mn></mrow> <mrow><mn> 2 </mn></mrow></mfrac></mrow> <mrow><mn> 3 </mn></mrow></mfrac> </mrow> </math>\n" +
                    "</body> </html>");
        } catch (Exception e) {
            Assertions.fail();
        }
    }

    @Test
    public void test5() {
        try {
            String s = "\\begin{document}\n" +
                    "    $ \\tiny $\n" +
                    "    $ a = 2 + 2 * 2 $\n" +
                    "\\end{document}";
            Assertions.assertEquals(convert(s), "<html> <head> <title> Tex2HTML </title> </head> <body>\n" +
                    "<div class=\"tiny\"></div>\n" +
                    "<math displaystyle=\"true\"> <mrow> <mi> a </mi> <mo> = </mo> <mrow> <mn> 2 </mn> <mo> + </mo> <mrow> <mn> 2 </mn> <mo> * </mo> <mn> 2 </mn> </mrow> </mrow> </mrow>  </math>\n" +
                    "</body> </html>");
        } catch (Exception e) {
            Assertions.fail();
        }
    }

    @Test
    public void test6() {
        try {
            String s = "\\begin{document}\n" +
                    "   $ $ \n" +
                    "   $ \\large $ \n" +
                    "    $ a = 2 + 2 * 2 + (1 - C^{(zw)^{asd_{c / 8}}}_{\\frac{1}{2 + 3}})$\n" +
                    "\\end{document}";
            Assertions.assertEquals(convert(s), "<html> <head> <title> Tex2HTML </title> </head> <body>\n" +
                    "<div class=\"large\"></div>\n" +
                    "<math displaystyle=\"true\"> <mrow> <mi> a </mi> <mo> = </mo> <mrow> <mrow> <mn> 2 </mn> <mo> + </mo> <mrow> <mn> 2 </mn> <mo> * </mo> <mn> 2 </mn> </mrow> </mrow> <mo> + </mo> <mrow> <mo> ( </mo> <msubsup> <mrow> <mn> 1 </mn> <mo> - </mo> <mi> C </mi> </mrow> <mfrac> <mrow><mn> 1 </mn></mrow> <mrow><mrow> <mn> 2 </mn> <mo> + </mo> <mn> 3 </mn> </mrow></mrow></mfrac> <msup> <mrow> <mo> ( </mo> <mi> zw </mi> <mo> ) </mo> </mrow> <msub> <mi> asd </mi> <mrow> <mi> c </mi> <mo> / </mo> <mn> 8 </mn> </mrow> </msub> </msup> </msubsup> <mo> ) </mo> </mrow> </mrow> </mrow>  </math>\n" +
                    "</body> </html>");
        } catch (Exception e) {
            Assertions.fail();
        }
    }
}
