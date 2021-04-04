package ticTacToe;

import java.util.Random;

public class RandomPlayer implements Player {
    private final int n, m;

    public RandomPlayer(int n, int m) {
        this.n = n;
        this.m = m;
    }

    public Move move(final LockedPosition position, final CellType cell) {
        while (true) {
            int r = new Random().nextInt(n);
            int c = new Random().nextInt(m);
            final Move move = new Move(r, c, cell);
            if (position.isValid(move)) {
                return move;
            }
        }
    }
}
