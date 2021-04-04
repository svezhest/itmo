package markup;

import java.util.List;

public class ListItem extends AbstractTex {
    private List<Listable> content;

    public ListItem(List<Listable> content) {
        this.texOp = "\\item ";
        this.content = content;
    }

    protected void toTex(StringBuilder sb, String op, String ed) {
        sb.append(op);
        for (Texable li : content) {
            li.toTex(sb);
        }
        Paragraph p1 = new Paragraph(List.of(new Text("1")));
        new UnorderedList(List.of(new ListItem(List.of(p1))));
    }
}
