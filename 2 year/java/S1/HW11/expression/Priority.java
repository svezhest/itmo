package expression;

public class Priority {
    private PriorityLevels level;
    private boolean isOrdered;

    Priority(PriorityLevels level, boolean isOrdered) {
        this.level = level;
        this.isOrdered = isOrdered;
    }

    public int getValue() {
        return level.value;
    }

    public boolean isOrdered() {
        return isOrdered;
    }
}
