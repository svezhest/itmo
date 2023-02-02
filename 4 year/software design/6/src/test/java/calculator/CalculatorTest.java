package calculator;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CalculatorTest {
    @Test
    void basic() {
        int result = Calculator.calculate("(30 + 2) / 8", false);
        assertEquals(4, result);
    }

    @Test
    void singleNumber() {
        int result = Calculator.calculate("42", false);
        assertEquals(42, result);
    }

    @Test
    void integerDivision() {
        int result = Calculator.calculate("(30 + 2) / 7", false);
        assertEquals(4, result);
    }

    @Test
    void difficult() {
        int result = Calculator.calculate("(30 + 2) / 8 + 1 * (9 + (7 / 2) - 3 - 2 - 1) / 2", false);
        assertEquals(7, result);
    }

    @Test
    void negative() {
        int result = Calculator.calculate("0 - 1", false);
        assertEquals(-1, result);
    }

    @Test
    void notAnExpression() {
        assertThrows(java.lang.RuntimeException.class, () -> {
            Calculator.calculate("hello there", false);
        });
    }

    @Test
    void badExpressions() {
        assertThrows(java.lang.RuntimeException.class, () -> {
            Calculator.calculate("()", false);
        });
        assertThrows(java.lang.RuntimeException.class, () -> {
            Calculator.calculate("1)", false);
        });
        assertThrows(java.lang.RuntimeException.class, () -> {
            Calculator.calculate("(1", false);
        });
        assertThrows(java.lang.RuntimeException.class, () -> {
            Calculator.calculate("(1 + ) 1", false);
        });
        assertThrows(java.lang.RuntimeException.class, () -> {
            Calculator.calculate("1 ( + 1)", false);
        });
        assertThrows(java.lang.RuntimeException.class, () -> {
            Calculator.calculate("(1 + ) ( 1)", false);
        });
        assertThrows(java.lang.RuntimeException.class, () -> {
            Calculator.calculate("+ 1", false);
        });
        assertThrows(java.lang.RuntimeException.class, () -> {
            Calculator.calculate("1 * / 1", false);
        });

        assertThrows(java.lang.RuntimeException.class, () -> {
            Calculator.calculate("1 1", false);
        });
    }
}