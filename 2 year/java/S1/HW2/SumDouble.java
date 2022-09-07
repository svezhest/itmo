public class SumDouble {
    public static void main(String[] args) {
        double result = 0.0 ;
        int start = 0;
        for (String input: args) {
            for (int i = 0; i < input.length(); i++) {
                if (!Character.isWhitespace(input.charAt(i))) {
                    start = i++;
                    while (i < input.length() && !Character.isWhitespace(input.charAt(i))) {
                        i++;
                    }
                    result += Double.parseDouble(input.substring(start, i));
                    i--;
                }
            }
        }
        System.out.println(result);
    }
}