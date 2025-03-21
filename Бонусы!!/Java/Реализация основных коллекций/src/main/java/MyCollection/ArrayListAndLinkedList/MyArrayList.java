package MyCollection.ArrayListAndLinkedList;

import lombok.EqualsAndHashCode; //Переопределяет equals и hashCode

import java.util.Arrays;
import java.util.Iterator;

@EqualsAndHashCode
public class MyArrayList<T> implements MyList<T> {

    Object[] array = new Object[10];
    int size = 0;

    @Override
    public boolean add(T t) {
        increaseArraySize();
        array[size++] = t;
        return true;
    }

    @Override
    public int size() {
        return size;
    }

    @SuppressWarnings("unchecked")
    @Override
    public T get(int index) {
        checkIndex(index);
        return (T) array[index];
    }

    @Override
    public boolean removeAt(int index) {
        checkIndex(index);
        System.arraycopy(array, index + 1, array, index, size - index - 1);
        array[--size] = null;
        return true;
    }

    @Override
    public void clear() {
        for (int i = 0; i < size; i++) {
            array[i] = null;
        }
        array = new Object[10];
        size = 0;
    }

    @Override
    public boolean contains(T t) {
        for (int i = 0; i < size; i++) {
            if (array[i].equals(t)) {
                return true;
            }
        }
        return false;
    }


    @Override
    public boolean insert(T t, int index) {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException();
        }
        increaseArraySize();
        System.arraycopy(array, index, array, index + 1, size - index);
        array[index] = t;
        size++;
        return true;
    }

    @Override
    public boolean remove(T item) {
        for (int i = 0; i < size; i++) {
            if (array[i].equals(item)) {
                return removeAt(i);
            }
        }
        return false;
    }

    private void checkIndex(int index) throws IndexOutOfBoundsException {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException();
        }
    }

    private void increaseArraySize() {
        if (size >= array.length) {
            array = Arrays.copyOf(array, array.length * 2);
        }
    }

    @Override
    public Iterator<T> iterator() {
        return new Iterator<>() {

            private int index = 0;

            @Override
            public boolean hasNext() {
                return index < size;
            }

            @SuppressWarnings("unchecked")
            @Override
            public T next() {
                return (T) array[index++];
            }
        };
    }
}