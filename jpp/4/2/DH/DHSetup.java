
import java.util.Random;

public class DHSetup<T extends GF> {

  private T generator;

  private T generateGenerator(T dum) {
    Random random = new Random();
    long number = random.nextLong(dum.getCharacteristic() - 1) + 1;
    return (T) new GF(number);
  }

  public DHSetup(T dum) {
    this.generator = generateGenerator(dum);
  }

  public T getGenerator() {
    return generator;
  }

  public T power(T a, long b) {
    if (b == 0) {
        return (T) new GF(1);
    }
    T temp = power(a, b/2);
    if (b % 2 == 0) {
      return (T) temp.mult(temp);
    } else {
      return (T) a.mult(temp).mult(temp);
    }
  }
}
