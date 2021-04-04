package ticTacToe;

public final class Move {
    private final int row;
    private final int column;
    private final CellType value;

    public Move(final int row, final int column, final CellType value) {
        this.row = row;
        this.column = column;
        this.value = value;
    }

    public int getRow() {
        return row;
    }

    public int getColumn() {
        return column;
    }

    public CellType getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "row=" + row + ", column=" + column + ", symbol=" + value;
    }
}
