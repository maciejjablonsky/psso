package gof.prototype;

public class Engine implements java.io.Serializable {
	private double displacement;
	private int power;

	Engine(double displacement, int power) {
		this.displacement = displacement;
		this.power = power;
	}

	public void tune() {
		power = power + 25;
	}

	public String toString() {
		return " displacement: " + displacement + "\n power: " + power;
	}

	@Override
	public int hashCode() {
		int hash = 3;
		hash = 29 * hash
				+ (int) (Double.doubleToLongBits(this.displacement) ^ (Double.doubleToLongBits(this.displacement) >>> 32));
		hash = 29 * hash + this.power;
		return hash;
	}

	@Override
	public boolean equals(Object obj) {
		if (obj == null) return false;
		if (getClass() != obj.getClass()) return false;
		final Engine other = (Engine) obj;
		if (Double.doubleToLongBits(this.displacement) != Double.doubleToLongBits(other.displacement)) {
			return false;
		}
		if (this.power != other.power) return false;
		return true;
	}

}
