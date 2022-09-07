package parser;

public class GraphCreator {
    private static void toGraphHelper(int n, Parser.Node node, StringBuilder stringBuilder) {
        stringBuilder.append(String.format("  %d [label=\"%s\"]\n", n, node.getType()));
        int add = 0;
        for (int i = 0; i < node.getListSize(); i++) {
            int childNum = n + 1 + add;
            toGraphHelper(childNum, node.getNthChild(i), stringBuilder);
            stringBuilder.append(String.format("  %d -> %d\n", n, childNum));
            add += node.getNthChild(i).getTreeSize();
        }
    }


    public static StringBuilder toGraph(Parser.Node node) {
        StringBuilder stringBuilder = new StringBuilder("digraph {\n");
        toGraphHelper(1, node, stringBuilder);
        stringBuilder.append("}\n");
        return stringBuilder;
    }
}
