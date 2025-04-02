package MyCollection.Map;

import java.util.List;
import java.util.Set;

public interface MyMap <K, V> {
    void put(K key, V value);

    V get(K key);

    boolean remove(K key);

    Set<K> keySet();

    List<V> values();

    int size();

    void clear();

}
