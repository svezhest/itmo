package ticTacToe;

import java.util.Arrays;
import java.util.Map;

public class Cell {
    private CellType type;
    private int[] neighbours = new int[8];
    private int xPos, yPos;

    private static final Map<CellType, Character> SYMBOLS = Map.of(
            CellType.X, 'X',
            CellType.O, 'O',
            CellType.E, '.',
            CellType.I, '|',
            CellType.H, '-'
    );

    Cell(CellType type, int x, int y) {
        this.type = type;
        Arrays.fill(neighbours, 0);
        this.xPos = x;
        this.yPos = y;
    }

    public char getChar() {
        return SYMBOLS.get(type);
    }

    private int toCode(int i, int j) {
        int x = 3 * (i + 1) + (j + 1);
        return x > 4 ? x - 1 : x;
    }

    public int getXPos() {
        return xPos;
    }

    public int getYPos() {
        return yPos;
    }

    public CellType getType() {
        return type;
    }

    public void setType(CellType type) {
        this.type = type;
    }

    public void setNeighbour(int i, int j, int x) {
        neighbours[toCode(i, j)] = x;
    }

    public int getNeighbour(int i, int j) {
        return neighbours[toCode(i, j)];
    }
}
