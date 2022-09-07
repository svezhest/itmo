import java.util.Scanner;

public class I {
    static int divideUp(int a, int b) {
        int r = a/b;
        return b * r < a ? r + 1 : r;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int xi;
        int yi;
        int hi;
        int xl = Integer.MAX_VALUE, xr = Integer.MIN_VALUE, yl = Integer.MAX_VALUE, yr = Integer.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            xi = in.nextInt();
            yi = in.nextInt();
            hi = in.nextInt();
            xl = Integer.min(xl, xi - hi);
            xr = Integer.max(xr, xi + hi);
            yl = Integer.min(yl, yi - hi);
            yr = Integer.max(yr, yi + hi);
        }
        System.out.println((xl + xr) / 2 + " " + (yl + yr) / 2 + " " + divideUp(Integer.max(xr - xl, yr - yl), 2));
    }
}
