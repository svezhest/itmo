import java.io.*;
import java.util.*;

public class ReverseMin {
    static int min(int a, int b) {
        if (a > b) {
            return b;
        }
        return a;
    }
    
    public static void main(String[] args) throws IOException {
        CustomScanner in = new CustomScanner(System.in);
        int [] colMin = new int [8];
        colMin[0] = Integer.MAX_VALUE;
        for (int i = 0; i < 8; i++) {
            colMin[i] = Integer.MAX_VALUE;
        }
        int [] strSize = new int [8];
        int [] strMin = new int [8];
        int str = 0;
        
        while (in.hasNextChar()) {
            if (str == strSize.length) {
                strSize = Arrays.copyOf(strSize, str*2);
                strMin = Arrays.copyOf(strMin, str*2);
            }
            CustomScanner curStr = new CustomScanner(in.nextLine());
            int col = 0;
            strMin[str] = Integer.MAX_VALUE;
            
            while (true) {
                int t;
                try {
                    t = curStr.nextInt();
                } catch (Exception e) {
                    break;
                }
                if (col == colMin.length) {
                    colMin = Arrays.copyOf(colMin, col*2);
                    for (int i = col; i < col * 2; i++) {
                        colMin[i] = Integer.MAX_VALUE;
                    }
                }
                strMin[str] = min(strMin[str], t);
                colMin[col] = min(colMin[col], t);
                col++;
            }
            
            strSize[str] = col;
            str++;
        }
        
        for (int i = 0; i < str; i++) {
            for (int j = 0; j < strSize[i]; j++) {
                System.out.print(min(strMin[i], colMin[j]) + " ");
            }
            System.out.println();
        }
    }

    static class CustomScanner {
        private BufferedReader reader;
        private char[] buffer = new char[1024];
        private int len, pos;
        private boolean EOF = false;

        public CustomScanner(InputStream inputstream) {
            reader = new BufferedReader(new InputStreamReader(inputstream));
        }

        public CustomScanner(String string) {
            reader = new BufferedReader(new StringReader(string));
        }

        private void readBuffer() throws IOException {
            len = reader.read(buffer);
            while (len == 0) {
                len = reader.read(buffer);
            }
            if (len == -1) {
                EOF = true;
            }
            pos = 0;
        }

        public boolean hasNextLine() throws IOException {
            return hasNextChar();
        }

        public char nextChar() throws IOException {
            if (pos >= len) {
                readBuffer();
            }
            return buffer[pos++];
        }

        public boolean hasNextChar() throws IOException {
            if (pos >= len) {
                readBuffer();
            }
            return !EOF;
        }

        public String nextLine() throws IOException {
            StringBuilder temp = new StringBuilder();
            char c;
            while (hasNextChar()) {
                c = nextChar();
//                if (c == '\r') {
//                    c = nextChar();
//                    break;
//                }
                if (c == '\n') {
                    break;
                }
                temp.append(c);
            }
            return temp.toString();
        }

        private void skipWhitespace() throws IOException {
            while (hasNextChar()) {
                char c = nextChar();
                if (!Character.isWhitespace(c)) {
                    break;
                }
            }
            pos--;
        }

        public String next() throws IOException {
            skipWhitespace();
            StringBuilder temp = new StringBuilder();
            char c;
            while (hasNextChar()) {
                c = nextChar();
                if (!Character.isWhitespace(c)) {
                    temp.append(c);
                } else break;
            }
            return temp.toString();
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }
}
