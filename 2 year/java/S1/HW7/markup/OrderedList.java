package markup;

import java.util.List;

public class OrderedList extends AbstractTexList {
    public OrderedList(List<ListItem> content) {
        super(content, "enumerate");
    }
}