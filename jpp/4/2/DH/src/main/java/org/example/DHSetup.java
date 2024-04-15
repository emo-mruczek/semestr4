package org.example;

import java.util.Random;

public class DHSetup<T extends GF> {

  private final T generator;

  private T generateGenerator() {
    T dum = null;
    Random random = new Random();
    long number = random.nextLong(dum.getCharacteristic() - 1) + 1;
    return (T) new T(number);
  }

  public DHSetup() {
    this.generator = generateGenerator();
  }

  public T getGenerator() {
    return generator;
  }

  T power(T a, long b) {
    T temp = new T();
    if (b == 0) {
        return (T) new Object
    }
  }


}
