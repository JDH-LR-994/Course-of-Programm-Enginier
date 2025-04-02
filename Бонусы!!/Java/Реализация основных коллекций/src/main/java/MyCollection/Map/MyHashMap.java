package MyCollection.Map;

import lombok.AllArgsConstructor;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class MyHashMap<K, V> implements MyMap<K, V> {
    private int size = 0;
    private static final int DEFAULT_INITIAL_CAPACITY = 16;
    private static final double DEFAULT_LOAD_FACTOR = 0.75;
    @SuppressWarnings("unchecked")
    private Entry<K, V>[] array = new Entry[DEFAULT_INITIAL_CAPACITY];

    @Override
    public void put(K key, V value) {
        if (size >= array.length * DEFAULT_LOAD_FACTOR) {
            increaseArray();
        }
        boolean res = put(key, value, array);
        if (res) size++;
    }

    private boolean put(K key, V value, Entry<K, V>[] dst) {
        int position = getElementPosition(key, dst.length);
        var existedElement = dst[position];
        if (existedElement == null) {
            var entry = new Entry<K, V>(key, value, null);
            dst[position] = entry;
            return true;
        } else {
            while (true) {
                if (existedElement.key.equals(key)) {
                    existedElement.value = value;
                    return false;
                }
                if (existedElement.next == null) {
                    existedElement.next = new Entry<>(key, value, null);
                    return true;
                }
                existedElement = existedElement.next;
            }
        }
    }

    private int getElementPosition(K key, int arrayLength) {
        if (key == null) {
            return 0;
        }
        return Math.abs(key.hashCode() % arrayLength);
    }

    @Override
    public V get(K key) {
        int position = getElementPosition(key, array.length);
        var element = array[position];
        while (element != null) {
            if (element.key.equals(key)) {
                return element.value;
            }
            element = element.next;
        }
        return null;
    }

    @Override
    public boolean remove(K key) {
        int position = getElementPosition(key, array.length);
        var element = array[position];
        if (element != null && element.key.equals(key)) {
            array[position] = element.next;
            size--;
            return true;
        } else {
            while (element != null) {
                var nextElement = element.next;
                if (nextElement == null) {
                    return false;
                }
                if (nextElement.key.equals(key)) {
                    element.next = nextElement.next;
                    size--;
                    return true;
                }
                element = nextElement;
            }
        }
        return false;
    }

    @Override
    public Set<K> keySet() {
        Set<K> keySet = new HashSet<>();
        for (var entry : array) {
            var existedElement = entry;
            while (existedElement != null) {
                keySet.add(existedElement.key);
                existedElement = existedElement.next;
            }
        }
        return keySet;
    }

    @Override
    public List<V> values() {
        List<V> listValues = new ArrayList<>();
        for (var entry : array) {
            var existedElement = entry;
            while (existedElement != null) {
                listValues.add(existedElement.value);
                existedElement = existedElement.next;
            }
        }
        return listValues;
    }

    @Override
    public int size() {
        return size;
    }

    @SuppressWarnings("unchecked")
    private void increaseArray(){
        Entry<K, V>[] newArray = new Entry[array.length * 2];
        for (var entry : array) {
            var existedElement = entry;
            while (existedElement != null) {
                put(existedElement.key, existedElement.value, newArray);
                existedElement = existedElement.next;
            }
        }
        array = newArray;
    }

    @Override
    @SuppressWarnings("unchecked")
    public void clear() {
        array = new Entry[DEFAULT_INITIAL_CAPACITY];
        size = 0;
    }

    @AllArgsConstructor
    private static class Entry<K, V> {
        K key;
        V value;
        Entry<K, V> next;
    }
}
