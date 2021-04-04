package markup;

import java.util.List;

public class Strikeout extends AbstractElement implements Primitive {
    public Strikeout(List<Primitive> content) {
        super(content, "~", "textst");
    }
}
