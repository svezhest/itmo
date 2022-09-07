package expression.calculators;

public interface Calculator<E extends Number> {
    E add(E a, E b);

    E subtract(E a, E b);

    E multiply(E a, E b);

    E divide(E a, E b);

    E negate(E x);

    E count(E x);

    E max(E a, E b);

    E min(E a, E b);

    E parse(String s);
}