package expression.calculators;

public class UncheckedIntegerCalculator implements Calculator<Integer> {
        @Override
        public Integer add(Integer a, Integer b) {
            return a + b;
        }

        @Override
        public Integer subtract(Integer a, Integer b) {
            return a - b;
        }

        @Override
        public Integer multiply(Integer a, Integer b) {
            return a * b;
        }

        @Override
        public Integer divide(Integer a, Integer b) {
            return a / b;
        }

        @Override
        public Integer negate(Integer x) {
            return -x;
        }

        @Override
        public Integer count(Integer x) {
            return Integer.bitCount(x);
        }

        @Override
        public Integer max(Integer a, Integer b) {
            return a > b ? a : b;
        }

        @Override
        public Integer min(Integer a, Integer b) {
            return a < b ? a : b;
        }

        @Override
        public Integer parse(String s) {
            return Integer.parseInt(s);
        }
    }
