package calculator;

import java.util.Scanner;

import static calculator.Calculator.calculate;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        System.out.println(calculate(input, true));
    }
}
