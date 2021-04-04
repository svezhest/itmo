import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class M {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        for (int it = 0; it < t; it++) {
            Map<Integer, Integer> map = new HashMap<>();
            int n = in.nextInt();
            int answ = 0;
            int[] a = new int [n];
            for (int i = 0; i < n; i++) {
                a[i] = in.nextInt();
                map.put(a[i], 0);
            }
            for (int j = n - 1; j >= 0; j--) {
                for (int i = 0; i < j; i++) {
                    answ += map.getOrDefault(2 * a[j] - a[i], 0);
                }
                map.put(a[j], map.get(a[j]) + 1);
            }
            System.out.println(answ);
        }
    }
}
