import java.util.concurrent.locks.ReentrantLock;

/**
 * Bank implementation.
 *
 * <p>:TODO: This implementation has to be made thread-safe.
 *
 * @author :TODO: LastName FirstName
 */
public class BankImpl implements Bank {
    /**
     * An array of accounts by index.
     */
    private final Account[] accounts;

    /**
     * Creates new bank instance.
     * @param n the number of accounts (numbered from 0 to n-1).
     */
    public BankImpl(int n) {
        accounts = new Account[n];
        for (int i = 0; i < n; i++) {
            accounts[i] = new Account();
        }
    }

    @Override
    public int getNumberOfAccounts() {
        return accounts.length;
    }

    /**
     * <p>:TODO: This method has to be made thread-safe.
     */
    @Override
    public long getAmount(int index) {
        accounts[index].lock.lock();
        long t = accounts[index].amount;
        accounts[index].lock.unlock();
        return t;
    }

    /**
     * <p>:TODO: This method has to be made thread-safe.
     */
    @Override
    public long getTotalAmount() {
        for (Account account : accounts) {
            account.lock.lock();
        }
        long sum = 0;
        for (Account account : accounts) {
            sum += account.amount;
        }
        for (Account account : accounts) {
            account.lock.unlock();
        }
        return sum;
    }

    /**
     * <p>:TODO: This method has to be made thread-safe.
     */
    @Override
    public long deposit(int index, long amount) {
        if (amount <= 0)
            throw new IllegalArgumentException("Invalid amount: " + amount);
        Account account = accounts[index];
        account.lock.lock();
        long t;
        try {
            if (amount > MAX_AMOUNT || account.amount + amount > MAX_AMOUNT)
                throw new IllegalStateException("Overflow");
            account.amount += amount;
            t = account.amount;
        } finally {
            account.lock.unlock();
        }
        return t;
    }

    /**
     * <p>:TODO: This method has to be made thread-safe.
     */
    @Override
    public long withdraw(int index, long amount) {
        if (amount <= 0)
            throw new IllegalArgumentException("Invalid amount: " + amount);
        Account account = accounts[index];
        account.lock.lock();
        long t;
        try {
            if (account.amount - amount < 0)
                throw new IllegalStateException("Underflow");
            account.amount -= amount;
            t = account.amount;
        } finally {
            account.lock.unlock();
        }
        return t;
    }

    /**
     * <p>:TODO: This method has to be made thread-safe.
     */
    @Override
    public void transfer(int fromIndex, int toIndex, long amount) {
        if (amount <= 0)
            throw new IllegalArgumentException("Invalid amount: " + amount);
        if (fromIndex == toIndex)
            throw new IllegalArgumentException("fromIndex == toIndex");
        Account from = accounts[fromIndex];
        Account to = accounts[toIndex];
        if (fromIndex < toIndex) {
            from.lock.lock();
            to.lock.lock();
        } else {
            to.lock.lock();
            from.lock.lock();
        }
        try {
            if (amount > from.amount)
                throw new IllegalStateException("Underflow");
            else if (amount > MAX_AMOUNT || to.amount + amount > MAX_AMOUNT)
                throw new IllegalStateException("Overflow");
            from.amount -= amount;
            to.amount += amount;
        } finally {
            if (fromIndex < toIndex) {
                from.lock.unlock();
                to.lock.unlock();
            } else {
                to.lock.unlock();
                from.lock.unlock();
            }
        }
    }

    /**
     * Private account data structure.
     */
    static class Account {
        /**
         * Amount of funds in this account.
         */
        long amount;

        ReentrantLock lock = new ReentrantLock();
    }
}
