package MyCollection.ArrayListAndLinkedList;

public interface MyList<T> extends Iterable<T> {
    void add(T t);
    int size();
    T get(int index);
    boolean removeAt(int index);
    void clear();
    void insert(T t, int index);
    boolean remove(T item);
}
