import MyCollection.ArrayListAndLinkedList.MyArrayList;
import MyCollection.ArrayListAndLinkedList.MyList;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MyListTest {

    private MyList<String> myArrayList;

    @BeforeEach
    public void setUp() {
        myArrayList = new MyArrayList<>();
        for (int i = 0; i < 100; i++) {
            myArrayList.add(String.valueOf(i));
        }
    }

    @Test
    public void whenAdded100ElementsThenSizeMustBe100() {
        assertEquals(100, myArrayList.size());
    }

    @Test
    public void whenElementRemovedByIndexThenSizeMustBeDecreased() {
        assertTrue(myArrayList.removeAt(5));
        assertEquals(99, myArrayList.size());
    }

    @Test
    public void whenElementRemovedThenSizeMustBeDecreased() {
        String car = "Toyota";
        myArrayList.add(car);
        assertEquals(101, myArrayList.size());
        assertTrue(myArrayList.remove(car));
        assertEquals(100, myArrayList.size());
    }

    @Test
    public void whenNonExistentElementRemovedThenReturnFalse() {
        String string = "Toyota";
        assertFalse(myArrayList.remove(string));
        assertEquals(100, myArrayList.size());
    }

    @Test
    public void whenListClearedThenSizeMustBe0() {
        myArrayList.clear();
        assertEquals(0, myArrayList.size());
    }

    @Test
    public void whenIndexOutOfBoundsThenThrownException() {
        assertThrows(IndexOutOfBoundsException.class, () -> myArrayList.get(100));
    }

    @Test
    public void methodGetReturnedRightValue() {
        String string = myArrayList.get(0);
        assertEquals("0", string);
    }

    @Test
    public void insertIntoMiddle() {
        String string = "BMW";
        myArrayList.insert(string, 50);
        assertEquals("BMW", myArrayList.get(50));
    }

    @Test
    public void insertIntoFirstPosition() {
        String string = "BMW";
        myArrayList.insert(string, 0);
        assertEquals("BMW", myArrayList.get(0));
    }

    @Test
    public void insertIntoLastPosition() {
        String string = "BMW";
        myArrayList.insert(string, myArrayList.size()); // Вставка в конец списка
        assertEquals("BMW", myArrayList.get(myArrayList.size() - 1)); // Проверка последнего элемента
        assertEquals(101, myArrayList.size()); // Проверка размера
    }
    @Test
    public void checkContainsWithoutElement() {
        String string = "BMW";
        assertFalse(myArrayList.contains(string));
    }
    @Test
    public void checkContainsWithElement() {
        String string = "1";
        assertTrue(myArrayList.contains(string));
    }
}