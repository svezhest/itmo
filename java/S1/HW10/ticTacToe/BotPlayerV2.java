package ticTacToe;

import java.util.Random;

public class BotPlayerV2 implements Player {
    private final int n, m, k;
    private Random random;
    private int x = -1, y = -1;

    public BotPlayerV2(int n, int m, int k) {
        this.n = n;
        this.m = m;
        this.k = k;
        this.random = new Random();
    }

    private void writeMove(Cell cell, boolean priority) {
        if (priority) {
            x = cell.getXPos();
            y = cell.getYPos();
        } else if (random.nextBoolean()) {
            x = cell.getXPos();
            y = cell.getYPos();
        }
    }

    public Move move(final LockedPosition position, final CellType cell) {
        int pMax = -1, tMax = -1;
        Cell temp, emptyCell;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                emptyCell = position.getCell(i, j);
                if (emptyCell.getType() != CellType.E) {
                    continue;
                }
                int type = (i == 0 || i == n - 1 ? 0 : 1)
                        + (j == 0 || j == m - 1 ? 0 : 1);
                for (int it = -1; it <= 1; it++) {
                    for (int jt = -1; jt <= 1; jt++) {
                        if (it == 0 && jt == 0) {
                            continue;
                        }
                        temp = position.getCell(i + it, j + jt);
                        if (temp == null) {
                            continue;
                        }
                        if (temp.getType() == cell) {
                            if (temp.getNeighbour(it, jt) * 2 + 2 > pMax) {
                                pMax = temp.getNeighbour(it, jt) * 2 + 2;
                                tMax = type;
                                writeMove(emptyCell, true);
                            } else if (temp.getNeighbour(it, jt) * 2 + 2 == pMax) {
                                if (type > tMax) {
                                    tMax = type;
                                    writeMove(emptyCell, true);
                                } else if (type == tMax) {
                                    writeMove(emptyCell, false);
                                }
                            }
                        } else if (temp.getType() == CellType.E) {
                            if (0 > pMax) {
                                pMax = 0;
                                tMax = type;
                                writeMove(emptyCell, true);
                            } else if (0 == pMax) {
                                if (type > tMax) {
                                    tMax = type;
                                    writeMove(emptyCell, true);
                                } else if (type == tMax) {
                                    writeMove(emptyCell, false);
                                }
                            }
                        } else {
                            if (temp.getNeighbour(it, jt) * 2 + 1 > pMax) {
                                pMax = temp.getNeighbour(it, jt) * 2 + 1;
                                tMax = type;
                                writeMove(emptyCell, true);
                            } else if (temp.getNeighbour(it, jt) * 2 + 1 == pMax) {
                                if (type > tMax) {
                                    tMax = type;
                                    writeMove(emptyCell, true);
                                } else if (type == tMax) {
                                    writeMove(emptyCell, false);
                                }
                            }
                        }
                    }
                }
            }
        }
        return new Move(x, y, cell);
    }
}
