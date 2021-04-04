package expression;

public enum  PriorityLevels {
    LOW(0),
    MEDIUM(1),
    HIGH(2);
    int value;

    PriorityLevels(int value) {
        this.value = value;
    }
}