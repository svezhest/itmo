import java.io.*;
import java.util.*;

public class ReverseSum {
    public static void main(String[] args) throws IOException {
        Scannerr in = new Scannerr(System.in);
        int [][] input = new int[1][];
        int [] colsum = new int[1];
        int [] strsize = new int[1];
        int [] strsum = new int[1];
        int str = 0;
        while (in.hasNextLine()) {
            if (str == input.length) {
                input = Arrays.copyOf(input, str*2);
                strsize = Arrays.copyOf(strsize, str*2);
                strsum = Arrays.copyOf(strsum, str*2);
            }
            Scannerr lil_in = new Scannerr(in.nextLine());
            int col = 0;
            strsum[str] = 0;
            input[str] = new int[1];
            while (true) {
                int t;
                try {
                    t = lil_in.nextInt();
                } catch (Exception e) {
                    break;
                }
                if (col == input[str].length) {
                    input[str] = Arrays.copyOf(input[str], col*2);
                    if (col == colsum.length) { 
                        colsum = Arrays.copyOf(colsum, col*2);
                    }
                }
                input[str][col] = t;
                strsum[str] += t;
                colsum[col] += t;
                col++;
            }
            strsize[str] = col;
            str++;
        }
        for (int i = 0; i < str; i++) {
            for (int j = 0; j < strsize[i]; j++) {
                System.out.print((strsum[i] + colsum[j] - input[i][j]) + " ");
            }
            System.out.println();
        }
    }
    static class Scannerr {
        private BufferedReader reader;
        private int bufLen = 2048;
        private char[] buffer = new char[bufLen];
        private int len, pos;
        private boolean EOF = false;

        public Scannerr(InputStream inputstream) {
            reader = new BufferedReader(new InputStreamReader(inputstream));
        }

        public Scannerr(String string) {
            reader = new BufferedReader(new StringReader(string));
        }

        public Scannerr(File file) throws FileNotFoundException {
            reader = new BufferedReader(new FileReader(file));
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
            nextChar();
            pos--;
            return !EOF;
        }

        public String nextLine() throws IOException {
            StringBuilder sb = new StringBuilder();
            char c;
            while (hasNextChar()) {
                c = nextChar();
                String l = System.lineSeparator();
                if (c == '\n' || c == '\r') {
                    break;
                }
                sb.append(c);
            }
            return sb.toString();
        }

        private void skipBlank() throws IOException {
            while (hasNextChar() && Character.isWhitespace(nextChar())) ;
            pos--;
        }

        public String next() throws IOException {
            skipBlank();
            StringBuilder sb = new StringBuilder();
            char c;
            while (hasNextChar()) {
                c = nextChar();
                if (!Character.isWhitespace(c)) {
                    sb.append(c);
                } else break;
            }
            return sb.toString();
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        public double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }

        public long nextLong() throws IOException {
            return Long.parseLong(next());
        }

        public byte nextByte() throws IOException {
            return Byte.parseByte(next());
        }

        public short nextShort() throws IOException {
            return Short.parseShort(next());
        }

        public float nextFloat() throws IOException {
            return Float.parseFloat(next());
        }
    }
}

