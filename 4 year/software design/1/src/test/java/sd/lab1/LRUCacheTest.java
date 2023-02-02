package sd.lab1;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class LRUCacheTest {

    @Test
    void basic() {
        int maximumCapacity = 5;
        LRUCache<Integer, Integer> lruCache = new LRUCache<Integer, Integer>(maximumCapacity);
        assertEquals(0, lruCache.size());
        assertEquals(maximumCapacity, lruCache.getMaximumCapacity());
        lruCache.put(1, 2);
        assertEquals(1, lruCache.size());
        assertEquals(2, lruCache.get(1));
    }

    @Test
    void zeroCapacity() {
        assertThrows(AssertionError.class, () -> {
            LRUCache<Integer, Integer> lruCache = new LRUCache<Integer, Integer>(0);
        });
    }

    @Test
    void oneElementCapacityUpdateCorrectness() {
        int maximumCapacity = 1;
        LRUCache<Integer, Integer> lruCache = new LRUCache<Integer, Integer>(maximumCapacity);
        assertEquals(0, lruCache.size());
        assertEquals(maximumCapacity, lruCache.getMaximumCapacity());
        lruCache.put(1, 2);
        assertEquals(1, lruCache.size());
        assertEquals(2, lruCache.get(1));
        lruCache.put(1, 3);
        assertEquals(1, lruCache.size());
        assertEquals(3, lruCache.get(1));
        lruCache.put(2, 4);
        assertEquals(1, lruCache.size());
        assertEquals(4, lruCache.get(2));
        assertNull(lruCache.get(1));
    }

    @Test
    void oneElementCapacityFlood() {
        int maximumCapacity = 1;
        LRUCache<Integer, Integer> lruCache = new LRUCache<Integer, Integer>(maximumCapacity);
        for (int i = 0; i < 1000; i++) {
            assertEquals(Math.min(maximumCapacity, i), lruCache.size());
            lruCache.put(i, i);
            for (int j = 0; j < Math.max(0, i + 1 - maximumCapacity); j++) {
                assertNull(lruCache.get(j));
            }
            for (int j = Math.max(0, i + 1 - maximumCapacity); j <= i; j++) {
                assertEquals(j, lruCache.get(j));
            }
        }
    }

    @Test
    void twoElementCapacityUpdateCorrectness() {
        int maximumCapacity = 2;
        LRUCache<Integer, Integer> lruCache = new LRUCache<Integer, Integer>(maximumCapacity);
        assertEquals(0, lruCache.size());
        assertEquals(maximumCapacity, lruCache.getMaximumCapacity());
        lruCache.put(1, 2);
        assertEquals(1, lruCache.size());
        assertEquals(2, lruCache.get(1));
        lruCache.put(2, 3);
        assertEquals(2, lruCache.size());
        assertEquals(3, lruCache.get(2));
        assertEquals(2, lruCache.get(1));
        lruCache.put(1, 4);
        assertEquals(2, lruCache.size());
        assertEquals(3, lruCache.get(2));
        assertEquals(4, lruCache.get(1));
        lruCache.put(3, 5);
        assertEquals(2, lruCache.size());
        assertEquals(5, lruCache.get(3));
        assertEquals(4, lruCache.get(1));
        assertNull(lruCache.get(2));
    }

    @Test
    void twoElementCapacityFlood() {
        int maximumCapacity = 2;
        LRUCache<Integer, Integer> lruCache = new LRUCache<Integer, Integer>(maximumCapacity);
        for (int i = 0; i < 1000; i++) {
            assertEquals(Math.min(maximumCapacity, i), lruCache.size());
            lruCache.put(i, i);
            for (int j = 0; j < Math.max(0, i + 1 - maximumCapacity); j++) {
                assertNull(lruCache.get(j));
            }
            for (int j = Math.max(0, i + 1 - maximumCapacity); j <= i; j++) {
                assertEquals(j, lruCache.get(j));
            }
        }
    }

    @Test
    void bigCapacityFlood() {
        int maximumCapacity = 200;
        LRUCache<Integer, Integer> lruCache = new LRUCache<Integer, Integer>(maximumCapacity);
        for (int i = 0; i < 1000; i++) {
            assertEquals(Math.min(maximumCapacity, i), lruCache.size());
            lruCache.put(i, i);
            for (int j = 0; j < Math.max(0, i + 1 - maximumCapacity); j++) {
                assertNull(lruCache.get(j));
            }
            for (int j = Math.max(0, i + 1 - maximumCapacity); j <= i; j++) {
                assertEquals(j, lruCache.get(j));
            }
        }
    }
}