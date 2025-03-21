package MyCollection.ArrayListAndLinkedList;

import MyCollection.MyCollection;

public interface MyList<T> extends MyCollection<T> {
    T get(int index);
    boolean removeAt(int index);
    boolean insert(T t, int index);
}
