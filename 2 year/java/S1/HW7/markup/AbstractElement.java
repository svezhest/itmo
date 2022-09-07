package markup;

import java.util.List;

public abstract class AbstractElement extends AbstractMarkdown {
    private List<Markable> content;

    public AbstractElement(List content, String md, String tex) {
        this.content = content;
        this.mdOp = md;
        this.mdEd = md;
        this.texOp = Generators.genTexOp(tex);
        this.texEd = "}";
    }

    protected void toTex(StringBuilder sb, String op, String ed) {
        sb.append(op);
        for (Texable t: content) {
            t.toTex(sb);
        }
        sb.append(ed);
    }

    protected void toMarkdown(StringBuilder sb, String op, String ed) {
        sb.append(op);
        for (Markable m : content) {
            m.toMarkdown(sb);
        }
        sb.append(ed);
    }
}
