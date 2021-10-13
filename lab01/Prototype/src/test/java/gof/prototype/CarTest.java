package gof.prototype;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.lang.reflect.InvocationTargetException;

import static org.junit.jupiter.api.Assertions.*;

class CarTest {
    @Test
    @DisplayName("Shallow Copy")
    void testShallowCopy() throws InvocationTargetException, NoSuchMethodException, NoSuchFieldException, InstantiationException, IllegalAccessException {
        Car audi = new Car("A6", 1.9, 130);
        Car bmw = audi.shallowClone();
        assertNotSame(audi, bmw);
        assertSame(audi.engine, bmw.engine);
    }

    @Test
    @DisplayName("Johnny Deep Copy")
    void testDeepCopy(){
        Car audi = new Car("A6", 1.9, 130);
        Car bmw = audi.deepClone();
        assertNotSame(audi, bmw);
        assertNotSame(audi.engine, bmw.engine);
    }

}