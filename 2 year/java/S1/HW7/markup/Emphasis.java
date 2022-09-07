package markup;

import java.util.List;

public class Emphasis extends AbstractElement implements Primitive {
    public Emphasis(List<Primitive> content) {
        super(content,"*", "emph");
    }
}
