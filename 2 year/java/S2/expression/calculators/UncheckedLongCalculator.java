package expression.calculators;

public class UncheckedLongCalculator implements Calculator<Long> {
    @Override
    public Long add(Long a, Long b) {
        return a + b;
    }

    @Override
    public Long subtract(Long a, Long b) {
        return a - b;
    }

    @Override
    public Long multiply(Long a, Long b) {
        return a * b;
    }

    @Override
    public Long divide(Long a, Long b) {
        return a / b;
    }

    @Override
    public Long negate(Long x) {
        return -x;
    }

    @Override
    public Long count(Long x) {
        return (long) Long.bitCount(x);
    }

    @Override
    public Long max(Long a, Long b) {
        return a > b ? a : b;
    }

    @Override
    public Long min(Long a, Long b) {
        return a < b ? a : b;
    }

    @Override
    public Long parse(String s) {
        return Long.parseLong(s);
    }
}
