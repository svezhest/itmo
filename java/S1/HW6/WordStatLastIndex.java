import javax.swing.text.html.parser.Entity;
import java.io.*;
import java.util.LinkedHashMap;
import java.util.Map;

public class WordStatLastIndex {
    public static void main(String[] args) throws IOException {
        Map<String, IntList> map = new LinkedHashMap<>();
        CustomScanner in = new CustomScanner(new File(args[0]));
        FileWriter output = new FileWriter(new File(args[1]));
        while (in.hasNextChar()) {
            for (IntList word: map.values()) {
                word.set(0, 0);
                // "Not in this line" flag
            }
            int numberInLine = 0;
            CustomScanner strIn = new CustomScanner(in.nextLine());
            while (strIn.hasNextChar()) {
                numberInLine++;
                String word;
                word = strIn.nextWord().toLowerCase();
                if (word.isEmpty()) {
                    break;
                }
                if (map.get(word) != null) {
                    IntList counters = map.get(word);
                    counters.inc(1);
                    if (counters.get(0) != 0) { // That word is in this line
                        counters.set(counters.getSize() - 1, numberInLine);
                    } else {
                        counters.inc(0);
                        counters.append(numberInLine);
                    }
                } else {
                    IntList counters = new IntList();
                    counters.set(0, 1); // "That word is in this line" flag
                    counters.set(1, 1); // Counter
                    counters.set(2, numberInLine);
                    map.put(word, counters);
                }
            }
        }
        for (Map.Entry<String, IntList> entry: map.entrySet()) {
            output.write(entry.getKey());
            IntList counters = entry.getValue();
            for (int i = 1; i < counters.getSize(); i++) {
                output.write(" " + counters.get(i));
            }
            output.write('\n');
        }
        in.close();
        output.close();
    }
}
