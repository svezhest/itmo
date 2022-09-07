package markup;

public class Text implements Primitive {
    private String content;

    public Text(String str) {
        this.content = str;
    }

    public void toMarkdown(StringBuilder sb) {
        sb.append(content);
    }

    public void toTex (StringBuilder sb) {
        sb.append(content);
    }
}
