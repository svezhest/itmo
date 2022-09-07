import java.io.*;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class WordStatCount {
    private static class Counter {
        public String word;
        public int howMany;
        public int firstApp;
        Counter(String temp, int k) {
            this.word = temp;
            this.howMany = 1;
            this.firstApp = k;
        }
    }
    public static void main(String[] args) throws IOException {
        FileWriter output = new FileWriter(new File(args[1]));
        CustomScanner in = new CustomScanner(new File(args[0]));
//        CustomScanner in = new CustomScanner(System.in);
//        Writer output = new OutputStreamWriter(System.out);
        List<Counter> cnt = new ArrayList<>();
        int number = 0;

        while (in.hasNextChar()) {
            String word;
            try {
                word = in.nextWord().toLowerCase();
            } catch (IOException e) {
                continue;
            }
            number++;
            int i;
            for (i = 0; i < cnt.size(); i++) { // linear search
                if (cnt.get(i).word.equals(word)) {
                    cnt.get(i).howMany++;
                    break;
                }
            }
            if (i == cnt.size()) { // add word
                cnt.add(new Counter(word, number));
            }
        }
        
    	Comparator<Counter> comp = Comparator.comparingInt((Counter a) -> a.howMany).thenComparingInt(a -> a.firstApp);
        cnt.sort(comp);
        for (int i = 0; i < cnt.size(); i++) {
            output.write(cnt.get(i).word + " " + cnt.get(i).howMany + '\n');
        }
        in.close();
        output.close();
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
            if (pos >= len) {
                readBuffer();
            }
            return !EOF;
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
                throw new IOException("No words in input :(");
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

        public void close() throws IOException {
            reader.close();
        }
    }
}


