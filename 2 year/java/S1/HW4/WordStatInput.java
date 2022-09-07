import java.io.*;
import java.util.Arrays;

public class WordStatInput {
    private static class Counter {
        public String word;
        public int howmany;
        public int first_app;
        Counter(String temp, int k) {
            this.word = temp;
            this.howmany = 1;
            this.first_app = k;
        }
        Counter(Counter example) {
            this.word = example.word;
            this.howmany = example.howmany;
            this.first_app = example.first_app;
        }
    }
    public static void main(String[] args) throws IOException {
//        FileReader input = new FileReader(new File(args[0]));
//        FileWriter output = new FileWriter(new File(args[1]));
        Reader input = new InputStreamReader(System.in);
        Writer output = new OutputStreamWriter(System.out);
        Counter[] cnt = new Counter[1];
        int words = 0, number = 0;
        while (true) {
            int ch = input.read();
            StringBuilder wordTemp = new StringBuilder();
            while (!(Character.isLetter(ch) || Character.DASH_PUNCTUATION == Character.getType(ch) || ch == '\'' || ch == -1)) {
                ch = input.read();
            }
            if (ch == -1) {
                break;
            }
            while (Character.isLetter(ch) || Character.DASH_PUNCTUATION == Character.getType(ch) || ch == '\'') {
                wordTemp.append((char) ch);
                ch = input.read();
            }
            String word = wordTemp.toString().toLowerCase();
            number++;
            int i;
            for (i = 0; i < words; i++) {
                if (cnt[i].word.equals(word)) {
                    cnt[i].howmany++;
                    break;
                }
            }
            if (i == words) { // new word
                if (i >= cnt.length) {
                    cnt = Arrays.copyOf(cnt, i * 2 + 1);
                }
                cnt[i] = new Counter(word, number);
                words++;
            }
        }
        insrSort(cnt, words);
        for (int i = 0; i < words; i++) {
            output.write(cnt[i].word + " " + cnt[i].howmany + '\n');
        }
        input.close();
        output.close();
    }
    private static void insrSort(Counter[] array, int length) {
        for (int i = 1; i < length; i++) {
            Counter next = new Counter(array[i]);
            int j = i - 1;
            while (j >= 0 && next.first_app < array[j].first_app) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = next;
        }
    }
}

