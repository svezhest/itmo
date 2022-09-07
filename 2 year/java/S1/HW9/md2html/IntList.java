package md2html;

import java.util.Arrays;

public class IntList {

    private int pos = -1;
    private int[] content;

    public IntList() {
        this.content = new int[64];
    }

    public IntList(int initSize) {
        this.content = new int[initSize];
    }

    private void smartResize(int checkPos) {
        if (checkPos >= this.content.length){
            this.content = Arrays.copyOf(this.content, (int) (this.content.length * 1.5));
        }
    }

    public void add(int x) {
        smartResize(++pos);
        this.content[this.pos] = x;
    }

    public void set(int pos, int x) {
        this.content[pos] = x;
        if (pos > this.pos) {
            this.pos = pos;
        }
    }

    public int get(int pos) {
        return this.content[pos];
    }

    public int pop() {
        return get(pos--);
    }

    public void multiPop(int newLastElPos) {
        if (newLastElPos < pos) {
            pos = newLastElPos;
        } // else do nothing
    }

    public int getSize() {
        return pos + 1;
    }

    public void inc(int pos) {
        this.content[pos]++;
    }

    public int findFirst(int x) {
        for (int i = 0; i <= pos; i++) {
            if (content[i] == x) {
                return i;
            }
        }
        return -1;
    }

    public int findLast(int x) {
        for (int i = pos; i >= 0; i--) {
            if (content[i] == x) {
                return i;
            }
        }
        return -1;
    }

    public int findFirstFrom(int pos, int x) {
        for (int i = pos + 1; i <= this.pos; i++) {
            if (content[i] == x) {
                return i;
            }
        }
        return -1;
    }

    public int findFirstBefore(int pos, int x) {
        for (int i = pos - 1; i >= 0; i--) {
            if (content[i] == x) {
                return i;
            }
        }
        return -1;
    }
}