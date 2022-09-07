package ticTacToe;

public class LockedPosition implements Position {
    private Position position;

    LockedPosition(Position board) {
        this.position = board;
    }

    public boolean isValid(Move move) {
        return position.isValid(move);
    }

    public Cell getCell(int r, int c) {
        return position.getCell(r, c);
    }

    public String toString() {
        return position.toString();
    }
}
