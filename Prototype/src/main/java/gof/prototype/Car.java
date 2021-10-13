package gof.prototype;

public class Car extends Prototype {
	  protected Engine engine;
	  protected String name;
	  protected int x,y;
	  
	  Car(String name, double displacement, int power) {
	    engine = new Engine(displacement, power);	
	    this.name=name;
	  }
	    
	  public void gotoXY(int x, int y) {
	  	this.x=x;
	  	this.y=y;
	  }	
	    
	  public String toString() {
	    return "name: "+ name + engine.toString() + " location: ("+x+";"+y+")\n";
	  }

	public void tune() {
	    engine.tune();
	  }
	
	@Override
	public int hashCode() {
        int hash = 7;
        hash = 41 * hash + this.engine.hashCode();
        hash = 41 * hash + this.name.hashCode();
        hash = 41 * hash + this.x;
        hash = 41 * hash + this.y;
        return hash;
	}

	@Override
	public boolean equals(Object obj) {
        if (obj == null) return false;        
        if (getClass() != obj.getClass()) return false;        
        final Car other = (Car) obj;
        if (!this.engine.equals(other.engine)) return false;        
        if (!this.name.equals(other.name)) return false;        
        if (this.x != other.x) return false;        
        if (this.y != other.y) return false;        
        return true;
	}
	    
}
