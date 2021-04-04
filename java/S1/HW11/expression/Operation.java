package expression;

public class Operation implements PriorityRanked {
    private final String type;
    private final Priority priority;

    Operation(String type) {
        this.type = type;
        switch (type) {
            case "+":
                this.priority = new Priority(PriorityLevels.LOW, false);
                break;
            case "-":
                this.priority = new Priority(PriorityLevels.LOW, true);
                break;
            case "*":
                this.priority = new Priority(PriorityLevels.MEDIUM, false);
                break;
            case "/":
                this.priority = new Priority(PriorityLevels.MEDIUM, true);
                break;
            default:
                throw new UnsupportedOperationException();
        }
    }

    public int doOperation(int a, int b) {
        switch (type) {
            case "+":
                return a + b;
            case "-":
                return a - b;
            case "*":
                return a * b;
            case "/":
                if (b == 0) {
                    throw new ArithmeticException("Division by zero");
                }
                return a / b;
            default:
                return -1;
        }
    }

    @Override
    public String toString() {
        return type;
    }

    @Override
    public Priority getPriority() {
        return priority;
    }
}
