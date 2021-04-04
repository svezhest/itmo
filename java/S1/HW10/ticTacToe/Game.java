package ticTacToe;

import java.util.Scanner;

public class Game {
    private final boolean log;
    private final Player[] players;
    Scanner in = new Scanner(System.in);
    public Game(final Player[] players, boolean log) {
        this.log = log;
        this.players = players;
    }

    public int play(Board board, int round) {
        log(board.getPosition().toString());
        while (true) {
            for (int i = 0; i < players.length; i++) {
                final int res = move(board, players[(i + round) % players.length],
                        (i + round) % players.length + 1);
                if (res != -1) {
                    return res;
                }
            }
        }
    }

    private int move(final Board board, final Player player, final int no) { ;
        final Move move = player.move(board.getPosition(), board.getTurn());
        final Result result = board.makeMove(move);
        log("Player " + no + " move: " + move);
        log(board.toString());
        if (result == Result.WIN) {
            return no;
        } else if (result == Result.BROKEN) {
            log("Somebody is ruining the game. Maybe cheating");
            return 0;
        } else if (result == Result.DRAW) {
            return 0;
        } else {
            return -1;
        }
    }

    private void log(final String message) {
        if (log) {
            System.out.println(message);
        }
    }
}
