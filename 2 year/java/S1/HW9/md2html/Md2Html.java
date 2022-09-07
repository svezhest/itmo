package md2html;

import java.io.*;
import java.nio.charset.StandardCharsets;

public class Md2Html {
    public static void main(String[] args) throws IOException {
        assert (args.length == 2);
        StringBuilder ans = new StringBuilder();
        CustomScanner cs = new CustomScanner(new File(args[0]));
        while (cs.hasNextLine()) {
            String s = cs.nextLine();
            StringBuilder sb = new StringBuilder();
            while (s != null && !s.equals("\n")) {
                sb.append(s);
                s = cs.nextLine();
            }
            if (sb.length() > 0) {
                sb.setLength(sb.length() - 1);
                new HtmlParser(sb).toHtml(ans);
                ans.append('\n');
            }
        }
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(new File(args[1])), StandardCharsets.UTF_8));
        bw.write(ans.toString());
        bw.close();
    }
}