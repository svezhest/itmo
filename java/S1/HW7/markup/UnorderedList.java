package markup;

import java.util.List;

public class UnorderedList extends AbstractTexList {
    public UnorderedList(List<ListItem> content) {
        super(content, "itemize");
    }
}
