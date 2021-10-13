package gof.prototype;

import java.io.*;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.ParameterizedType;
import java.util.ArrayList;
import java.util.List;

public interface IPrototype extends Serializable, Cloneable {

	default <T> T shallowClone() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, NoSuchFieldException {
		T clone = null;
		try {
			Method m = Object.class.getDeclaredMethod("clone");
			m.setAccessible(true);
			clone = (T) m.invoke(this);
		} catch (NoSuchMethodException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		}
		return clone;
	}
	default <T> T deepClone() {
		T clone = null;
		try {
			ByteArrayOutputStream baOUT = new ByteArrayOutputStream();
			ObjectOutputStream oOUT = new ObjectOutputStream(baOUT);
			oOUT.writeObject(this);

			ByteArrayInputStream baIN = new ByteArrayInputStream(baOUT.toByteArray());
			ObjectInputStream oIN = new ObjectInputStream(baIN);
			clone = (T) oIN.readObject();
		} catch (IOException | ClassNotFoundException e) {//Java 7 required
			e.printStackTrace();
		}
		return clone;
	}

}
