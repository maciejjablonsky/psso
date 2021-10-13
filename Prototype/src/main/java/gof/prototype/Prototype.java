package gof.prototype;

import java.io.*;

public class Prototype implements Cloneable, Serializable {
	public <T> T shallowClone() {
		T clone = null;
		try {
			clone = (T) super.clone();
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		return clone;
	}
	public <T> T deepClone() {
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
