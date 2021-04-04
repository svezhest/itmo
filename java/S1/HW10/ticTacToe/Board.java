package ticTacToe;

public interface Board {
    LockedPosition getPosition();

    CellType getTurn();

    Result makeMove(Move move);
}
