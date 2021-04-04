package expression.calculators;

public class UncheckedShortCalculator implements Calculator<Short> {
    @Override
    public Short add(Short a, Short b) {
        return (short) (a + b);
    }

    @Override
    public Short subtract(Short a, Short b) {
        return (short) (a - b);
    }

    @Override
    public Short multiply(Short a, Short b) {
        return (short) (a * b);
    }

    @Override
    public Short divide(Short a, Short b) {
        return (short) (a / b);
    }

    @Override
    public Short negate(Short x) {
        return (short) -x;
    }

    @Override
    public Short count(Short x) {
        return (short) Integer.bitCount(x & 0xffff);
    }

    @Override
    public Short max(Short a, Short b) {
        return a > b ? a : b;
    }

    @Override
    public Short min(Short a, Short b) {
        return a < b ? a : b;
    }

    @Override
    public Short parse(String s) {
        return (short) Integer.parseInt(s);
    }
}
