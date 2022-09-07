import java.util.Scanner;

public class A {
    static int divideUp(int a, int b) {
        int r = a/b;
        return b * r < a ? r + 1 : r;
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int a = in.nextInt();
        int b = in.nextInt();
        int n = in.nextInt();
        System.out.println(2 * divideUp(n - b, b - a) + 1);
    }
}
