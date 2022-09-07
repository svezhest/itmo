package md2html;

public class HtmlParser {
    StringBuilder content;
    IntList stack = new IntList();
    IntList posStack = new IntList();
    IntList tagInfo = new IntList();
    int pos, start = -1;
    String[][] tags = {{"<em>", "</em>", "*"},
            {"<em>", "</em>", "_"},
            {"<strong>", "</strong>", "**"},
            {"<strong>", "</strong>", "__"},
            {"<s>", "</s>", "--"},
            {"<code>", "</code>", "`"},
            {"<a href='", "", "["},
            {"'>", "", "]"},
            {"", "", "("},
            {"</a>", "", ")"}};


    private char after(int i) {
        Long.hashCode(2L);
        if (i + 1 == content.length()) {
            return ' ';
        }
        return content.charAt(i + 1);
    }

    private void appendHtmlChar(StringBuilder sb, char c) {
        switch (c) {
            case '<':
                sb.append("&lt;");
                break;
            case '>':
                sb.append("&gt;");
                break;
            case '&':
                sb.append("&amp;");
                break;
            case '\\':
                break;
            default:
                sb.append(c);
        }
    }

    private void htmlSubstring(StringBuilder sb, int l, int r) {
        for (int j = l + 1; j < r; j++) {
            appendHtmlChar(sb, content.charAt(j));
        }
    }

    public HtmlParser(StringBuilder sb) {
        this.content = sb;
    }

    public void toHtml(StringBuilder ans) {
        for (pos = 0; pos < content.length() && content.charAt(pos) == '#'; pos++) {
        }
        if (pos != 0 && (!(pos < content.length()) || Character.isWhitespace(content.charAt(pos)))) {
            String endTag = pos + ">";
            ans.append("<h").append(endTag);
            start = pos++;
            analyzeText(ans);
            ans.append("</h").append(endTag);
        } else {
            ans.append("<p>");
            analyzeText(ans);
            ans.append("</p>");
        }
    }

    private void toStacks(int intCode) {
        stack.add(intCode);
        posStack.add(pos);
        tagInfo.add(0);
    }

    private void analyzeText(StringBuilder ans) {
        while (pos < content.length()) {
            switch (content.charAt(pos)) {
                case '*':
                    if (after(pos) == '*') {
                        toStacks(2);
                        pos++;
                    } else {
                        toStacks(0);
                    }
                    break;
                case '_':
                    if (after(pos) == '_') {
                        toStacks(3);
                        pos++;
                    } else {
                        toStacks(1);
                    }
                    break;
                case '-':
                    if (after(pos) == '-') {
                        toStacks(4);
                        pos++;
                    }
                    break;
                case '`':
                    toStacks(5);
                    break;
                case '[':
                    toStacks(6);
                    break;
                case ']':
                    toStacks(7);
                    break;
                case '(':
                    toStacks(8);
                    break;
                case ')':
                    toStacks(9);
                    break;
                case '\\':
                    pos++;
            }
            pos++;
        }
        analyzeStack(ans, start, pos, 0, stack.getSize());
    }

    private void analyzeStack(StringBuilder ans, int textStart, int textEnd, int stackStart, int stackEnd) {
        for (int i = stackStart; i < stackEnd; i++) {
            htmlSubstring(ans, textStart, posStack.get(i));
            if (tagInfo.get(i) == 1) {
                ans.append(tags[stack.get(i)][1]);
            } else {
                if (stack.get(i) == 6) {
                    int f = stack.findFirstFrom(i, 7);
                    int f1 = stack.findFirstFrom(f, 8);
                    int f2 = stack.findFirstFrom(f1, 9);
                    if (f != -1 && f1 != -1 && f2 != -1) {
                        tagInfo.set(i, 1);
                        tagInfo.set(f, 1);
                        tagInfo.set(f1, 1);
                        tagInfo.set(f2, 1);
                        for (int j = f1 + 1; j < f2; j++) {
                            tagInfo.set(j, -1);
                        }

                        ans.append(tags[6][0]);
                        htmlSubstring(ans, posStack.get(f1), posStack.get(f2));
                        ans.append(tags[7][0]);
                        analyzeStack(ans, posStack.get(i), posStack.get(f), i + 1, f);
                        ans.append(tags[9][0]);

                        textStart = posStack.get(f2);
                        i = f2;
                        continue;
                    }
                } else if (stack.get(i) > 6 || tagInfo.get(i) == -1) {
                    ans.append(tags[stack.get(i)][2]);
                } else {
                    int f = stack.findFirstFrom(i, stack.get(i));
                    if (f == -1) {
                        ans.append(tags[stack.get(i)][2]);
                    } else {
                        ans.append(tags[stack.get(i)][0]);
                        tagInfo.set(f, 1);
                    }
                }
            }
            textStart = posStack.get(i);
            if (stack.get(i) == 2 || stack.get(i) == 3 || stack.get(i) == 4) {
                textStart++;
            }
        }
        htmlSubstring(ans, textStart, textEnd);
    }
}
