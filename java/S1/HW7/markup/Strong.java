package markup;

import java.util.List;

public class Strong extends AbstractElement implements Primitive {
    public Strong(List<Primitive> content) {
        super(content, "__", "textbf");
    }
}
