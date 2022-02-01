package parser;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.text.ParseException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws ParseException {
        Scanner scanner = new Scanner(System.in);
        String s = "fun absbbs(a : A, b : B, c : Int, d : D) : Uadlksfnsjaflkaj";

        InputStream stream = new ByteArrayInputStream(s.getBytes(StandardCharsets.UTF_8));
        LexicalAnalyzer l = new LexicalAnalyzer(stream);
        Parser parser = new Parser(l);
        Parser.Node root = parser.run();

        try {
            File myObj = new File("graph.dot");
            if (myObj.createNewFile()) {
                System.out.println("File created: " + myObj.getName());
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

        try {
            FileWriter myWriter = new FileWriter("graph.dot");
            myWriter.write(GraphCreator.toGraph(root).toString());
            myWriter.close();
            System.out.println("Successfully wrote to the file.");
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

    }
}
