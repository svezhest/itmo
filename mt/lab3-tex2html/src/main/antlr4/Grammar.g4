grammar Grammar;

tex returns [String value]:
   BEGIN next=line {
     $value = "<html> <head> <title> Tex2HTML </title> </head> <body>\n" + $next.value + "</body> </html>";
   }
;

line returns [String value]:
   '$' expr1=expression '=' expr2=expression '$' next=line {
     $value = "<math displaystyle=\"true\"> <mrow> " + $expr1.value + " <mo> = </mo> " + $expr2.value + " </mrow>  </math>\n" + $next.value;
   }
   | '$' expr=expression '$' next=line {
     $value = "<math displaystyle=\"true\"> <mrow> " + $expr.value + " </mrow> </math>\n" + $next.value;
   }
   | '$' '\\' s=Variable '$' next=line {
     $value = "<div class=\"" + $s.text + "\"></div>\n" + $next.value;
   }
   | '$' '$' next=line {
     $value = $next.value;
   }
   | END {
     $value = "";
   }
;

expression returns [String value]:
   '(' expr=expression ')' {
     $value = "<mrow> " + "<mo> ( </mo> " + $expr.value + " <mo> ) </mo>" + " </mrow>";
   }
   | expr1=expression sign=MulOrDiv expr2=expression {
     $value = "<mrow> " + $expr1.value + " <mo> " + $sign.text + " </mo> " + $expr2.value + " </mrow>";
   }
   | expr1=expression sign=('+' | '-') expr2=expression {
     $value = "<mrow> " + $expr1.value + " <mo> " + $sign.text + " </mo> " + $expr2.value + " </mrow>";
   }
   | expr1=expression UP OPEN_BRACKET expr2=expression CLOSE_BRACKET DOWN OPEN_BRACKET expr3=expression CLOSE_BRACKET {
     $value = "<msubsup> " + $expr1.value + " " + $expr3.value + " " + $expr2.value + " </msubsup>";
   }
   | expr1=expression DOWN OPEN_BRACKET expr2=expression CLOSE_BRACKET UP OPEN_BRACKET expr3=expression CLOSE_BRACKET {
     $value = "<msubsup> " + $expr1.value + " " + $expr2.value + " " + $expr3.value + " </msubsup>";
   }
   | <assoc=right> expr1=expression sign=(UP | DOWN) OPEN_BRACKET expr2=expression CLOSE_BRACKET {
     if ($sign.text.equals("^")) {
        $value ="<msup> " + $expr1.value + " " + $expr2.value + " </msup>";
     } else {
        $value ="<msub> " + $expr1.value + " " + $expr2.value + " </msub>";
     }
   }
   | '-' expr=expression {
     $value = "<mo> - </mo> " + $expr.value;
   }
   | '\\frac' OPEN_BRACKET expr1=expression CLOSE_BRACKET OPEN_BRACKET expr2=expression CLOSE_BRACKET {
     $value = "<mfrac> " + "<mrow>" + $expr1.value + "</mrow>" + " " + "<mrow>" + $expr2.value + "</mrow>" + "</mfrac>";
   }
   | s=object {
     $value = $s.value;
   }
;

object returns [String value]:
   s=Number {
     $value = "<mn> " + $s.text +" </mn>";
   }
   | s=Variable {
     $value = "<mi> " + $s.text +" </mi>";
   }
;

MulOrDiv: ('*' | '/' );

Whitespace: (' ' | '\t' | '\r' | '\n') -> skip;
Number: ('-')? ('0'..'9')+;

Variable: ('a'..'z' | 'A'..'Z')+;
OPEN_BRACKET : '{';
CLOSE_BRACKET : '}';
BEGIN : '\\begin' OPEN_BRACKET 'document' CLOSE_BRACKET;
END : '\\end' OPEN_BRACKET 'document' CLOSE_BRACKET;
UP : '^';
DOWN : '_';
