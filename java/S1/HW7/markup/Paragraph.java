package markup;

import java.util.List;

public class Paragraph implements Listable, Markdownable {
    private List<Primitive> content;

    public Paragraph(List<Primitive> content) {
        this.content = content;
    }

    public void toTex(StringBuilder sb) {
        for (Texable t: content) {
            t.toTex(sb);
        }
    }

    public void toMarkdown(StringBuilder sb) {
        for (Markable m : content) {
            m.toMarkdown(sb);
        }
    }
}
