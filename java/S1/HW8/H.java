import java.io.*;
import java.util.Scanner;
 
public class H {
    public static void main(String[] args) throws IOException {
        PrintWriter out = new PrintWriter(System.out);
        CustomScanner in = new CustomScanner(System.in);
        int n = in.nextInt();
        int [] a = new int[n];
        int [] link = new int[n];
        int maxA = Integer.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
            if (i == 0) {
                link[i] = 1;
            } else {
                link[i] = link[i - 1] + a[i - 1];
            }
            if (a[i] > maxA) {
                maxA = a[i];
            }
        }
        int A = link[n - 1] + a[n - 1] - 1;
        int [] f = new int[A + 1];
        f[0] = -1;
        int k = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < a[i]; j++) {
                f[k] = i;
                k++;
            }
        }
	int[] norep = new int [1000001];
	for (int i = 0; i < 1000001; i++) {
		norep[i]=0;
	}
        int t = in.nextInt();
 
        for (int i = 0; i < t; i++) {
            int q = in.nextInt();
            if (maxA > q) {
                out.println("Impossible");
                continue;
            }
	    if (norep[q] != 0) {
		out.println(norep[q]);
		continue;
	    }
            int answ = 0;
 
            for (int l = 1; l <= A; l += q) {
                l = link[f[l]];
                answ++;
            }
            out.println(answ);
	    norep[q]=answ;
        }
        out.flush();
    }
}
class CustomScanner {
    private BufferedReader reader;
    private char[] buffer = new char[8192];
    private int len, pos;
    private boolean EOF = false;
 
    public CustomScanner(InputStream inputstream) {
        reader = new BufferedReader(new InputStreamReader(inputstream));
    }
 
    public CustomScanner(String string) {
        reader = new BufferedReader(new StringReader(string));
    }
 
    public CustomScanner(File file) throws FileNotFoundException {
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
        StringBuilder temp = new StringBuilder();
        char c;
        while (hasNextChar()) {
            c = nextChar();
            if (c == '\n' || c == '\r') {
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
 
    private boolean isLetterOrPunct(char c) {
        return (Character.isLetter(c) || Character.DASH_PUNCTUATION == Character.getType(c) || c == '\'');
    }
 
    public String nextWord() throws IOException {
        StringBuilder temp = new StringBuilder();
        char c = nextChar();
        while (!isLetterOrPunct(c) && hasNextChar()) {
            c = nextChar();
        }
        if (!hasNextChar()) {
            return "";
        }
        while (isLetterOrPunct(c)) {
            temp.append(c);
            if (hasNextChar()) {
                c = nextChar();
            } else {
                break;
            }
        }
        return temp.toString();
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
 
    public void close() throws IOException {
        reader.close();
    }
}
