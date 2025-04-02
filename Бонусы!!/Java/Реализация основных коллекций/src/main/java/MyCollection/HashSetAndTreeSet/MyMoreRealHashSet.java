package MyCollection.HashSetAndTreeSet;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class MyMoreRealHashSet<T> implements MySet<T>{
    private final Map<T, Object> map = new HashMap<>();
    private final Object object = new Object();


    @Override
    public boolean add(T t) {
        if (map.containsKey(t)) {
            return false;
        }
        map.put(t, object);
        return true;
    }

    @Override
    public boolean remove(T t) {
        Object o = map.remove(t);
        return o != null;
    }

    @Override
    public int size() {
        return map.size();
    }

    @Override
    public void clear() {
        map.clear();
    }

    @Override
    public boolean contains(T t) {
        return map.containsKey(t);
    }

    @Override
    public Iterator<T> iterator() {
        return map.keySet().iterator();
    }
}
