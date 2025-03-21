import JDH.LR.Car;
import MyCollection.HashSetAndTreeSet.MyHashSet;
import MyCollection.HashSetAndTreeSet.MySet;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MySetTest {

    private MySet<Car> mySet;

    @BeforeEach
    void setUp() {
        mySet = new MyHashSet<>();
        for (int i = 0; i < 100; i++){
            mySet.add(new Car("Brand" + i, i));
        }
    }
    @Test
    public void whenAdd3SimilarObjectThenSizeIncreaseBy1(){
        assertEquals(100, mySet.size());
        assertTrue(mySet.add(new Car("BMW", 10)));
        assertFalse(mySet.add(new Car("BMW", 10)));
        assertFalse(mySet.add(new Car("BMW", 10)));
        assertEquals(101, mySet.size());
    }

    @Test
    public void whenSetClearedThenSize0(){
        mySet.clear();
        assertEquals(0, mySet.size());
    }

    @Test
    public void whenElementRemovedThenSizeDecreaseBy1(){
        assertTrue(mySet.remove(new Car("Brand30", 30)));
        assertEquals(99, mySet.size());
        assertFalse(mySet.remove(new Car("Brand30", 30)));
        assertEquals(99, mySet.size());
    }

    @Test
    public void checkContainsWithoutElement() {
        mySet.remove(new Car("Brand30", 30));
        assertFalse(mySet.contains(new Car("Brand30", 30)));
    }

    @Test
    public void checkContainsWithElement() {
        assertTrue(mySet.contains(new Car("Brand30", 30)));
    }

}