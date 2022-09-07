package markup;

import java.util.List;

public abstract class AbstractTexList extends AbstractTex implements Listable {
    private List<ListItem> content;

    public AbstractTexList(List<ListItem> content, String keyword) {
        this.texOp = Generators.genTexListOp(keyword);
        this.texEd = Generators.genTexListEd(keyword);
        this.content = content;
    }

    protected void toTex(StringBuilder sb, String op, String ed) {
        sb.append(op);
        for (ListItem li : content) {
            li.toTex(sb);
        }
        sb.append(ed);
    }
}
