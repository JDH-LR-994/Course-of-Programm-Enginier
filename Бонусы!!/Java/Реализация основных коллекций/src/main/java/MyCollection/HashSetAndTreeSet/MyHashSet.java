package MyCollection.HashSetAndTreeSet;

import lombok.AllArgsConstructor;
import lombok.EqualsAndHashCode;

import java.util.Iterator;
import java.util.NoSuchElementException;

@EqualsAndHashCode
public class MyHashSet<T> implements MySet<T> {

    private static final int INITIAL_CAPACITY = 16;
    private static final double LOAD_FACTOR = 0.75;
    private int size = 0;

    @SuppressWarnings("unchecked")
    private Entry<T>[] array = new Entry[INITIAL_CAPACITY];

    private int getElementPosition(T element, int arrayLength) {
        if (element == null) {
            return 0;
        }
        return Math.abs(element.hashCode() % arrayLength);
    }

    @Override
    public boolean add(T element) {
        if (size >= (array.length * LOAD_FACTOR)) {
            increaseArray();
        }
        boolean added = add(element, array);
        if (added) {
            size++;
        }
        return added;
    }


    private boolean add(T element, Entry<T>[] dst) {
        int position = getElementPosition(element, dst.length);
        if (dst[position] == null) {
            Entry<T> entry = new Entry<>(element, null);
            dst[position] = entry;
            return true;
        } else {
            Entry<T> existedElement = dst[position];
            while (true) {
                if (existedElement.value.equals(element)) {
                    return false;
                } else if (existedElement.next == null) {
                    existedElement.next = new Entry<>(element, null);
                    return true;
                } else {
                    existedElement = existedElement.next;
                }
            }
        }
    }

    @Override
    public boolean remove(T element) {
        int position = getElementPosition(element, array.length);
        if (array[position] == null) {
            return false;
        }
        Entry<T> secondLast = array[position];
        Entry<T> last = secondLast.next;
        if (secondLast.value.equals(element)) {
            array[position] = last;
            size--;
            return true;
        }
        while (last != null) {
            if (last.value.equals(element)) {
                secondLast.next = last.next;
                size--;
                return true;
            } else {
                secondLast = last;
                last = last.next;
            }
        }
        return false;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public void clear() {
        array = new Entry[INITIAL_CAPACITY];
        size = 0;
    }

    @Override
    public boolean contains(T t) {
        int position = getElementPosition(t, array.length);
        Entry<T> entry = array[position];
        while (entry != null) {
            if (entry.value.equals(t)) {
                return true;
            }
            entry = entry.next;
        }
        return false;
    }

    private void increaseArray() {
        @SuppressWarnings("unchecked")
        Entry<T>[] newArray = new Entry[array.length * 2];
        for (Entry<T> entry : array) {
            Entry<T> existedElement = entry;
            while (existedElement != null) {
                add(existedElement.value, newArray);
                existedElement = existedElement.next;
            }
        }
        array = newArray;
    }

    @Override
    public Iterator<T> iterator() {
        return new Iterator<>() {
            private int currentIndex = 0;
            private Entry<T> currentEntry = null;

            @Override
            public boolean hasNext() {
                while (currentIndex < array.length && currentEntry == null ) {
                    currentEntry = array[currentIndex++];
                }
                return currentEntry != null;
            }

            @Override
            public T next() {
                if (!hasNext()) {
                    throw new NoSuchElementException();
                }
                T value = currentEntry.value;
                currentEntry = currentEntry.next;
                return value;
            }
        };
    }

    @AllArgsConstructor
    private static class Entry<T> {
        private T value;
        private Entry<T> next;
    }
}
