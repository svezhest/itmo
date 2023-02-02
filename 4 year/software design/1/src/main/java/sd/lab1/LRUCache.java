package sd.lab1;

import java.util.HashMap;

public class LRUCache<Key, Value> {
    private class LinkedListEntry {
        LinkedListEntry next = null;
        LinkedListEntry prev = null;
        Value value;
        Key key;

        LinkedListEntry(Key key, Value value) {
            assert value != null;
            assert key != null;
            this.value = value;
            this.key = key;
        }

        void remove() {
            if (this.next != null) {
                this.next.prev = this.prev;
            }
            if (this.prev != null) {
                this.prev.next = this.next;
            }
            this.next = null;
            this.prev = null;
        }

        void insertEntryAfterThis(LinkedListEntry newEntry) {
            assert newEntry != null;
            assert this.next == null;
            assert newEntry.prev == null;
            assert newEntry.next == null;
            this.next = newEntry;
            newEntry.prev = this;
        }
    }

    private final HashMap<Key, LinkedListEntry> hashMap = new HashMap<>();
    private LinkedListEntry leastRecentlyUsed = null;
    private LinkedListEntry mostRecentlyUsed = null;
    private final int maximumCapacity;

    public LRUCache(int maximumCapacity) {
        assert maximumCapacity > 0;
        this.maximumCapacity = maximumCapacity;
    }

    //    invariant: size() <= getMaximumCapacity()
    public int size() {
        return hashMap.size();
    }

    public int getMaximumCapacity() {
        return maximumCapacity;
    }

    private void updateMostRecentlyUsed(LinkedListEntry newMostRecentlyUsed) {
        assert mostRecentlyUsed != null;
        assert newMostRecentlyUsed != null;
        if (mostRecentlyUsed == newMostRecentlyUsed) {
            return;
        }
        if (leastRecentlyUsed == newMostRecentlyUsed) {
            if (leastRecentlyUsed.next != null) {
                leastRecentlyUsed = leastRecentlyUsed.next;
            }
        }
        newMostRecentlyUsed.remove();
        mostRecentlyUsed.insertEntryAfterThis(newMostRecentlyUsed);
        assert mostRecentlyUsed.next == newMostRecentlyUsed;
        mostRecentlyUsed = newMostRecentlyUsed;
    }

    public Value get(Key key) {
        assert key != null;
        assert this.size() <= this.getMaximumCapacity();
        LinkedListEntry result = hashMap.get(key);
        if (result != null) {
            updateMostRecentlyUsed(result);
            assert result.value != null;
            assert this.size() <= this.getMaximumCapacity();
            return result.value;
        } else {
            assert this.size() <= this.getMaximumCapacity();
            return null;
        }
    }

    //    invariant: will always put value to the cache, i.e.
    //    {
    //      put(x,y);
    //      get(x) == y is always true
    //    }
    public void put(Key key, Value value) {
        assert this.size() <= this.getMaximumCapacity();
        assert key != null;
        assert value != null;
        LinkedListEntry result = hashMap.get(key);
        if (result != null) {
            updateMostRecentlyUsed(result);
            result.value = value;
        } else {
            if (hashMap.size() == 0) {
                LinkedListEntry newEntry = new LinkedListEntry(key, value);
                hashMap.put(key, newEntry);
                leastRecentlyUsed = newEntry;
                mostRecentlyUsed = newEntry;
            } else if (hashMap.size() == maximumCapacity) {
                hashMap.remove(leastRecentlyUsed.key);
                leastRecentlyUsed = leastRecentlyUsed.next;
                if (leastRecentlyUsed != null) {
                    assert hashMap.size() != 0;
                    leastRecentlyUsed.prev = null;
                }
                put(key, value);
            } else {
                LinkedListEntry newEntry = new LinkedListEntry(key, value);
                hashMap.put(key, newEntry);
                updateMostRecentlyUsed(newEntry);
            }
        }
        assert hashMap.get(key) != null;
        assert this.size() <= this.getMaximumCapacity();
    }
}