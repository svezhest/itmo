package md2html;

import java.io.*;

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
        if (!hasNextChar()) {
            return null;
        }
        StringBuilder temp = new StringBuilder();
        char c;
        while (hasNextChar()) {
            c = nextChar();
            if (c == '\n' || c == '\r') {
                temp.append('\n');
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
        if (!hasNextChar()) {
            return null;
        }
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

