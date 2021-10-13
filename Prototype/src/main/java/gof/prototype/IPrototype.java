package gof.prototype;

import java.io.*;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.ParameterizedType;

public interface IPrototype extends Cloneable, Serializable {
	default <T> T shallowClone() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, NoSuchFieldException {
		ParameterizedType superClass = (ParameterizedType) getClass().getGenericSuperclass();
		Class<T> clazzRoot = (Class<T>) superClass.getActualTypeArguments()[0];
		T newInstance = clazzRoot.getDeclaredConstructor().newInstance();
		Field[] fieldsClone = newInstance.getClass().getDeclaredFields();
		for (Field fieldClone : fieldsClone) {
			fieldClone.setAccessible(true);
			Field declaredField = clazzRoot.getDeclaredField(fieldClone.getName());
			declaredField.setAccessible(true);
			fieldClone.set(newInstance, (String) declaredField.get(clazzRoot));
		}
		return newInstance;
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
