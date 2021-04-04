package expression.calculators;

public class UncheckedDoubleCalculator implements Calculator<Double> {
    @Override
    public Double add(Double a, Double b) {
        return a + b;
    }

    @Override
    public Double subtract(Double a, Double b) {
        return a - b;
    }

    @Override
    public Double multiply(Double a, Double b) {
        return a * b;
    }

    @Override
    public Double divide(Double a, Double b) {
        return a / b;
    }

    @Override
    public Double negate(Double x) {
        return -x;
    }

    @Override
    public Double count(Double x) {
        return (double) Long.bitCount(Double.doubleToLongBits(x));
    }

    @Override
    public Double max(Double a, Double b) {
        return a > b ? a : b;
    }

    @Override
    public Double min(Double a, Double b) {
        return a < b ? a : b;
    }

    @Override
    public Double parse(String s) {
        return Double.parseDouble(s);
    }
}
