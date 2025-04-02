import JDH.LR.Car;
import JDH.LR.CarOwner;
import MyCollection.Map.MyHashMap;
import MyCollection.Map.MyMap;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MyMapTest {

    private MyMap<CarOwner, Car> map;

    @BeforeEach
    void setUp() {
        map = new MyHashMap<>();
    }

    @Test
    public void whenPut100ElementThenSizeBecome100(){
        for (int i = 0; i < 100; i++) {
            var carOwner = new CarOwner(i, "Name " + i, "Last Name " + i );
            var car = new Car("Brand " + i, i);
            map.put(carOwner, car);
        }
        assertEquals(100, map.size());
    }

    @Test
    public void whenPut100ElementsWith10DifferentKeysThenSizeBecome10(){
        for (int i = 0; i < 100; i++) {
            var carOwner = new CarOwner(i % 10, "Name " + i % 10, "Last Name " + i % 10);
            var car = new Car("Brand " + i % 10, i % 10);
            map.put(carOwner, car);
        }
        assertEquals(10, map.size());
    }

    @Test
    public void removeReturnTrueOnlyOnce() {
        for (int i = 0; i < 10; i++) {
            CarOwner carOwner = new CarOwner(i, "Name" + i, "LastName" + i);
            Car car = new Car("Brand" + i, i);
            map.put(carOwner, car);
        }
        assertEquals(10, map.size());

        CarOwner elementForDeleting = new CarOwner(5, "Name5", "LastName5");
        assertTrue(map.remove(elementForDeleting));
        assertEquals(9, map.size());
        assertFalse(map.remove(elementForDeleting));
    }

    @Test
    public void countOfKeysMustBeEqualsToCountOfValues() {
        for (int i = 0; i < 100; i++) {
            CarOwner carOwner = new CarOwner(i, "Name" + i, "LastName" + i);
            Car car = new Car("Brand" + i, i);
            map.put(carOwner, car);
        }
        assertEquals(100, map.size());
        assertEquals(100, map.keySet().size());
        assertEquals(100, map.values().size());
    }

    @Test
    public void methodGetMustReturnRightValue() {
        for (int i = 0; i < 100; i++) {
            CarOwner carOwner = new CarOwner(i, "Name" + i, "LastName" + i);
            Car car = new Car("Brand" + i, i);
            map.put(carOwner, car);
        }
        CarOwner key = new CarOwner(50, "Name50", "LastName50");
        Car value = map.get(key);
        String expectedCarBrand = "Brand50";
        assertEquals(expectedCarBrand, value.brand());
    }

}