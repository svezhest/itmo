package ticTacToe;

import java.util.Arrays;

public class BotPlayer implements Player {
    private final int n, m, k;
    private Cell[] topPlaces;
    public BotPlayer(int n, int m, int k) {
        this.n = n;
        this.m = m;
        this.k = k;
        topPlaces = new Cell[k * 2 + 1];
    }

    public Move move(final LockedPosition position, final CellType cell) {
        Arrays.fill(topPlaces, null);
        Cell temp, emptyCell;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                emptyCell = position.getCell(i, j);
                if (emptyCell.getType() != CellType.E) {
                    continue;
                }
                int notBorder = 0;
                for (int it = -1; it <= 1; it++) {
                    for (int jt = -1; jt <= 1; jt++) {
                        if (it == 0 && jt == 0) {
                            continue;
                        }
                        temp = position.getCell(i + it, j + jt);
                        if (temp == null) {
                            continue;
                        } else {
                            notBorder++;
                        }
                        if (temp.getType() == CellType.E) {
                            continue;
                        }
                        if (temp.getType() == cell) {
                            topPlaces[(temp.getNeighbour(it, jt) + 1) * 2 + 2] = emptyCell;
                        } else {
                            topPlaces[(temp.getNeighbour(it, jt) + 1) * 2 + 1] = emptyCell;
                        }
                    }
                }
                if (notBorder > 5) {
                    topPlaces[2] = emptyCell;
                } if (notBorder > 3) {
                    topPlaces[1] = emptyCell;
                } else {
                    topPlaces[0] = emptyCell;
                }
            }
        }
        for (int i = k * 2; i >= 0; i--) {
            if (topPlaces[i] != null) {
                return new Move(topPlaces[i].getXPos(), topPlaces[i].getYPos(), cell);
            }
        }
        return null;
    }
}
