package ticTacToe;

public interface Player {
    Move move(LockedPosition position, CellType cell);
}
