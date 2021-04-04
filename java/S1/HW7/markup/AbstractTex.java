package markup;

public abstract class AbstractTex implements Texable {
    protected String texOp;
    protected String texEd;

    protected void toTex(StringBuilder sb, String texOp, String texEd) {}

    public void toTex(StringBuilder sb) {
        toTex(sb, texOp, texEd);
    }
}
