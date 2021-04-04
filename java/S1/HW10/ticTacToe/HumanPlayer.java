package ticTacToe;

import java.io.PrintStream;
import java.util.InputMismatchException;
import java.util.Scanner;


public class HumanPlayer implements Player {
    private final PrintStream out;
    private final Scanner in;

    public HumanPlayer(final PrintStream out, final Scanner in) {
        this.out = out;
        this.in = in;
    }

    public HumanPlayer() {
        this(System.out, new Scanner(System.in));
    }

    public Move move(final LockedPosition position, final CellType cell) {
//        Board board = (Board) position;
        out.println(cell + "'s move");
        while (true) {
            out.println("Enter row and column");
            int r, c;
            try {
                r = in.nextInt();
                c = in.nextInt();
            } catch (InputMismatchException e) {
                out.println("U r stupid do it again");
                in.nextLine();
                continue;
            }
            final Move move = new Move(r, c, cell);
            if (position.isValid(move)) {
                return move;
            }
        }
    }
}
