package expression.generic;

import expression.CommonExpression;
import expression.calculators.*;
import expression.exceptions.SyntaxException;
import expression.parser.ExpressionParser;

import java.util.Map;

public class GenericTabulator implements expression.generic.Tabulator {
    private static final Map<String, Calculator<? extends Number>> CALCULATORS = Map.of(
            "u", new UncheckedIntegerCalculator(),
            "i", new CheckedIntegerCalculator(),
            "d", new UncheckedDoubleCalculator(),
            "bi", new UncheckedBigIntegerCalculator(),
            "l", new UncheckedLongCalculator(),
            "s", new UncheckedShortCalculator()
    );

    private static <E extends Number> Object[][][] run(final Calculator<E> calculator, final String expression, final int x1, final int x2, final int y1, final int y2, final int z1, final int z2) throws SyntaxException {
        final Object[][][] table = new Object[x2 - x1 + 1][y2 - y1 + 1][z2 - z1 + 1];
        final CommonExpression<E> formula = new ExpressionParser<>(calculator).parse(expression);
        for (int i = 0; i <= x2 - x1; i++) {
            for (int j = 0; j <= y2 - y1; j++) {
                for (int k = 0; k <= z2 - z1; k++) {
                    try {
                        table[i][j][k] = formula.evaluate(x1 + i, y1 + j, z1 + k);
                    } catch (final expression.exceptions.ArithmeticException ignored) {
//                    } catch ( ArithmeticException e2) {
                    }
                }
            }
        }
        return table;
    }

    @Override
    public Object[][][] tabulate(final String mode, final String expression, final int x1, final int x2, final int y1, final int y2, final int z1, final int z2) throws Exception {
        if (x2 < x1 || y2 < y1 || z2 < z1) {
            throw new IllegalArgumentException("Bounds are not correct");
        }
        // :NOTE: NPE
        return run(CALCULATORS.get(mode), expression, x1, x2, y1, y2, z1, z2);
    }
}
