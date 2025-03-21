package MyCollection;

public interface MyCollection<T> extends Iterable<T>{
    boolean add(T t);
    boolean remove(T t);
    int size();
    void clear();
    boolean contains(T t);
}
