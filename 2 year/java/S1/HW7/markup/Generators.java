package markup;

public class Generators {
    static public String genTexListOp(String word) {
        return new StringBuilder().append("\\begin{").append(word).append("}").toString();
    }
    static public String genTexListEd(String word) {
        return new StringBuilder().append("\\end{").append(word).append("}").toString();
    }
    static public String genTexOp(String word) {
        return new StringBuilder().append("\\").append(word).append("{").toString();
    }
}
