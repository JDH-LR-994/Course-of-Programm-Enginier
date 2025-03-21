package MyCollection.HashSetAndTreeSet;

import MyCollection.MyCollection;

public interface MySet<T> extends MyCollection<T> {
    boolean add(T t);
    boolean remove(T t);
    int size();
    void clear();
}
