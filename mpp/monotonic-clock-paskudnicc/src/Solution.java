import org.jetbrains.annotations.NotNull;

/**
 * В теле класса решения разрешено использовать только финальные переменные типа RegularInt.
 * Нельзя volatile, нельзя другие типы, нельзя блокировки, нельзя лазить в глобальные переменные.
 *
 * @author :TODO: Kryukov Alexandr
 */
public class Solution implements MonotonicClock {
    private final RegularInt c1 = new RegularInt(0);
    private final RegularInt c2 = new RegularInt(0);
    private final RegularInt c3 = new RegularInt(0);

    private final RegularInt r1 = new RegularInt(0);
    private final RegularInt r2 = new RegularInt(0);
    private final RegularInt r3 = new RegularInt(0);

    @Override
    public void write(@NotNull Time time) {
        r1.setValue(time.getD1());
        r2.setValue(time.getD2());
        r3.setValue(time.getD3());

        // write right-to-left
        c2.setValue(time.getD2());
        c1.setValue(time.getD1());
    }

    @NotNull
    @Override
    public Time read() {
//        r is latter
//        save from changer
        int e1 = c1.getValue();
        int e2 = c2.getValue();
        int l3 = r3.getValue();
        int l2 = r2.getValue();
        int l1 = r1.getValue();

        if (e1 == l1) {
            if (e2 == l2) {
                return new Time(l1, l2, l3);
            } else {
                return new Time(l1, l2, 0);
            }
        } else {
            return new Time(l1, 0, 0);
        }
    }
}
