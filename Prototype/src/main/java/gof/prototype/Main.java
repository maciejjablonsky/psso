package gof.prototype;

import java.lang.reflect.InvocationTargetException;

public class Main {
	  public static void main(String args[]) throws CloneNotSupportedException, InvocationTargetException, NoSuchMethodException, NoSuchFieldException, InstantiationException, IllegalAccessException {
	    Car audi = new Car("A6", 1.9, 130);
	    System.out.println("oryginal: "+audi);
	    Car copy1 = audi.deepClone();
	    Car copy2 = audi.shallowClone();
	    System.out.println("deepClone: "+copy1);
	    System.out.println("shallowClone: "+copy2);
	    
	    audi.gotoXY(20,30);
	    audi.tune();
	    System.out.println("oryginal after modyfications: "+audi);
	    System.out.println("deepClone: "+copy1);
	    System.out.println("shallowClone: "+copy2);
	  }
}
