import java.util.Scanner;

public class J {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.nextLine();
        int [][] ver = new int [n][n];
        for (int i = 0; i < n; i++) {
            String inp = in.nextLine();
            for (int j = 0; j < n; j++) {
                ver[i][j] = inp.charAt(j) - '0';
            }
        }
        int [][] answ = new int [n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                answ[i][j] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (ver[i][j] != 1) {
                    continue;
                }
                answ[i][j] = 1;
                for (int k = j + 1; k < n; k++) {
                    ver[i][k] = (ver[i][k] + 10 - ver[j][k]) % 10;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(answ[i][j]);
            }
            System.out.println();
        }
    }
}
