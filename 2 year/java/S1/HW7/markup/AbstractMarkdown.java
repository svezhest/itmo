package markup;

public abstract class AbstractMarkdown extends AbstractTex implements Markable {
    protected String mdOp;
    protected String mdEd;

    protected void toMarkdown(StringBuilder sb, String mdOp, String mdEd) {}

    public void toMarkdown(StringBuilder sb) {
        toMarkdown(sb, mdOp, mdEd);
    }
}
