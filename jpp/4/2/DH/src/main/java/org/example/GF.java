package org.example;

import java.util.Scanner;

public class GF {

  //scanner dla -1W!!!

  private static final long size = 1234567891;

  private long value;

  // konstruktory
  public GF() {
    this.value = 0;
  }

  public GF(long n) {
    if (n >= 0) {
      this.value = n % this.size;
    } else {
      this.value = ((this.size - (-n)) % this.size);
    }
  }

  // konwersja
  public static GF toGF(long n) {
    GF gf = new GF();
    gf.value = n % gf.size;
    return gf;
  }

  public long toLong() {
    return this.value;
  }

  // do zwracania charakterystyki
  public static long getCharacteristic() {
    return size;
  }

  // operatory porównań
  // ==
  public boolean equals(GF obj) {
    return this.value == obj.value;
  }

  // !=
  public boolean notEquals(GF obj) {
    return this.value != obj.value;
  }

  // <=
  public boolean lessEquals(GF obj) {
    return this.value <= obj.value;
  }

  // >=
  public boolean moreEquals(GF obj) {
    return this.value >= obj.value;
  }

  // <
  public boolean less(GF obj) {
    return this.value < obj.value;
  }

  // >
  public boolean more(GF obj) {
    return this.value > obj.value;
  }

  // operatory arytmetyczne
  // +
  public GF add(GF obj) {
    GF res = new GF();
    res.value = (this.value + obj.value) % this.size;
    return res;
  }

  // -
  public GF sub(GF obj) {
    GF res = new GF();
    res.value = (this.value - obj.value + this.size) % this.size;
    return res;
  }

  // *
  public GF mult(GF obj) {
    GF res = new GF();
    res.value = (this.value * obj.value) % this.size;
    return res;
  }

  // /
  public GF div(GF obj) throws ArithmeticException {
    if (obj.value == 0) {
      throw new ArithmeticException("Division by 0");
    }

    int inverse = 1;
    for (int i = 1; i < this.size; i++) {
      if ((obj.value * i) % this.size == 1) {
        inverse = i;
        break;
      }
    }

    GF res = new GF();
    res.value = (this.value * inverse) % this.size;
    return res;
  }

  // operatory podstawien
  // =
  public void assign(GF obj) {
    if (this.value != obj.value) {
      this.value = obj.value;
    }
  }

  // +=
  public void addTo(GF obj) {
    this.value = (this.value + obj.value) % this.size;
  }

  // -=
  public void subTo(GF obj) {
    this.value = (this.value - obj.value + this.size) % this.size;
  }

  // *=
  public void multTo(GF obj) {
    this.value = (this.value * obj.value) % this.size;
  }

  // /=
  public void divTo(GF obj) throws ArithmeticException {
    if (obj.value == 0) {
      throw new ArithmeticException("Division by 0");
    }

    int inverse = 1;
    for (int i = 1; i < this.size; i++) {
      if ((obj.value * i) % this.size == 1) {
        inverse = i;
        break;
      }
    }

    this.value = (this.value * inverse) % this.size;
  }


  // streamy
  // do printowania
  @Override
  public String toString() {
    return Long.toString(this.value);
  }

  // do scanneru
  public void read(Scanner scanner) {
    int temp = scanner.nextInt();
    this.value = temp % this.size;
  }
}

