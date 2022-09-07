package parser;

import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;

public class Parser {
    LexicalAnalyzer lex;
    Token curToken;

    public class Node {
        private String type;
        private List<Node> list;

        public Node(String type) {
            this.type = type;
            list = new ArrayList<>();
        }

        public String getType() {
            return type;
        }

        public Node getNthChild(int n) {
            return list.get(n);
        }

        public void addChild(Node node) {
            list.add(node);
        }

//        public void print() {
//            System.out.print(type);
//            if (!list.isEmpty()) {
//                System.out.print("<<");
//                list.forEach(Node::print);
//                System.out.print(">> ");
//            }
//        }

        public int getListSize() {
            return list.size();
        }

        public int getTreeSize() {
            int res = 1;
            for (Node node : list) {
                res += node.getTreeSize();
            }
            return res;
        }

    }

    public Parser(LexicalAnalyzer lex) {
        this.lex = lex;
    }

    private void advance() throws ParseException {
        lex.nextToken();
        curToken = lex.curToken();
    }

    public Node run() throws ParseException {
        advance();
        return S();
    }

    private void checkAndAdd(Node node, Token token) throws ParseException {
        if (curToken == token) {
            node.addChild(new Node(Token.getToken(token)));
            advance();
        } else {
            throw new ParseException("Unexpected symbol " + Token.getToken(curToken)
                    + ", expecting " + Token.getToken(token), lex.curPos());
        }
    }
//````
//    S  -> fun N ( V ) : G
//    V  -> eps
//    V  -> N : G V'
//    V' -> , N : G V'
//    V' -> eps
//    G -> T C
//    C -> eps
//    C -> < L >
//    L -> eps
//    L -> G L'
//    L' -> eps
//    L' -> , G L'
//    N  is terminal for word
//    T  is terminal for type
//````
//
//    First / Follow
//
//````
//    First                             Follow
//    S   |  fun                           |   $
//    V   |  n eps                         |   )
//    V'  |  , eps                         |   )
//    G   |  T                             |   eps , > $
//    C   |  < eps                         |   eps , > $
//    L   |  T eps                         |   >
//````
    public Node S() throws ParseException {
        Node root = new Node("S");
        switch (curToken) {
            case FUN -> {
                checkAndAdd(root, Token.FUN);
                checkAndAdd(root, Token.N);
                checkAndAdd(root, Token.LPAREN);
                root.addChild(V());
                checkAndAdd(root, Token.RPAREN);
                checkAndAdd(root, Token.COLON);
                root.addChild(G());
            }
            default -> throw new ParseException("Expected 'fun'", lex.curPos());
        }
        return root;
    }

    public Node V() throws ParseException {
        Node root = new Node("V");
        switch (curToken) {
            case N -> {
                checkAndAdd(root, Token.N);
                checkAndAdd(root, Token.COLON);
                root.addChild(G());
                root.addChild(VV());
            }
            case RPAREN -> {
                return root;
            }
            default -> throw new ParseException("Expected name or ')'", lex.curPos());
        }
        return root;
    }

    public Node VV() throws ParseException {
        Node root = new Node("V'");
        switch (curToken) {
            case COMMA -> {
                checkAndAdd(root, Token.N);
                checkAndAdd(root, Token.COLON);
                root.addChild(G());
                checkAndAdd(root, Token.COMMA);
                root.addChild(VV());
            }
            case RPAREN -> {
                return root;
            }
            default -> throw new ParseException("Expected name or ')'", lex.curPos());
        }
        return root;
    }

    public Node G() throws ParseException {
        Node root = new Node("G");
        switch (curToken) {
            case T -> {
                checkAndAdd(root, Token.T);
                root.addChild(C());
            }
            default -> throw new ParseException("Expected name or ')'", lex.curPos());
        }
        return root;
    }

    public Node C() throws ParseException {
        Node root = new Node("C");
        switch (curToken) {
            case LGEN -> {
                checkAndAdd(root, Token.LGEN);
                root.addChild(L());
                checkAndAdd(root, Token.RGEN);
            }
            case COMMA, RGEN, END -> {
                return root;
            }
            default -> throw new ParseException("Expected name or ')'", lex.curPos());
        }
        return root;
    }

    public Node L() throws ParseException {
        Node root = new Node("L");
        switch (curToken) {
            case RGEN -> {
                return root;
            }
            case T -> {
                root.addChild(G());
                root.addChild(LL());
            }
            default -> throw new ParseException("Expected name or ')'", lex.curPos());
        }
        return root;
    }

    public Node LL() throws ParseException {
        Node root = new Node("L'");
        switch (curToken) {
            case RGEN -> {
                return root;
            }
            case COMMA -> {
                checkAndAdd(root, Token.COMMA);
                root.addChild(G());
                root.addChild(LL());
            }
            default -> throw new ParseException("Expected name or ')'", lex.curPos());
        }
        return root;
    }
}
