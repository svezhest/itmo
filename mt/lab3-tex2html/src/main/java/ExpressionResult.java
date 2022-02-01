public class ExpressionResult {
    private final String name;
    private final double value;

    public ExpressionResult(String name, double value) {
        this.name = name;
        this.value = value;
    }

    public String getName() {
        return name;
    }

    public double getValue() {
        return value;
    }

    @Override
    public String toString() {
        return name + " = " + value;
    }
}
