public class Sum {
    public static void main(String[] args) {
        String input = "";
        for (String i: args) {
            input += i + " ";
        }
        int result = 0;
        String buff = "";
        for (int i = 0; i < input.length(); i++) {
            if (Character.isWhitespace(input.charAt(i))) {
                if (buff != "") {
                    result += Integer.parseInt(buff, 10);
                    buff = "";
                }
            } else {
                buff += input.charAt(i);
            }
        }
        System.out.println(result);
    }
}