import org.example.GF;

import java.util.Scanner;

public class Test {

  public static void main(String[] args) {
    System.out.println("Tworzę dwa obiekty: a i b");
    GF a = new GF();
    GF b = new GF();

    System.out.println("Ich obecne wartości to: a: " + a + " b: " + b);

    a.assign(GF.toGF(22));
    System.out.println("Podstawiam za a wartość 22: a: " + a);

    b.assign(a);
    System.out.println("Podstawiam a do b: b: " + b);

    System.out.println("-------");

    System.out.print("Czy a == b? ");
    System.out.println(a.equals(b) ? "prawda" : "fałsz");

    System.out.print("Czy a == 1? ");
    System.out.println(a.equals(GF.toGF(1)) ? "prawda" : "fałsz");

    System.out.print("Czy a == 22? ");
    System.out.println(a.equals(GF.toGF(22)) ? "prawda" : "fałsz");

    System.out.print("Czy a == 3? ");
    System.out.println(a.equals(GF.toGF(3)) ? "prawda" : "fałsz");

    System.out.println("-------");

    System.out.print("Czy a != b? ");
    System.out.println(a.notEquals(b) ? "prawda" : "fałsz");

    System.out.print("Czy a != 1? ");
    System.out.println(a.notEquals(GF.toGF(1)) ? "prawda" : "fałsz");

    System.out.print("Czy a != 22? ");
    System.out.println(a.notEquals(GF.toGF(22)) ? "prawda" : "fałsz");

    System.out.print("Czy a != 3? ");
    System.out.println(a.notEquals(GF.toGF(3)) ? "prawda" : "fałsz");

    System.out.println("-------");

    GF c = new GF(12);
    GF d = new GF(0);

    System.out.println("Tworzę c: " + c + " i d: " + d);

    System.out.print("Czy a <= c? ");
    System.out.println(a.lessEquals(c) ? "prawda" : "fałsz");

    System.out.print("Czy a > c? ");
    System.out.println(a.more(c) ? "prawda" : "fałsz");

    System.out.print("Czy a < 12? ");
    System.out.println(a.less(GF.toGF(12)) ? "prawda" : "fałsz");

    System.out.print("Czy a < d? ");
    System.out.println(a.less(d) ? "prawda" : "fałsz");

    System.out.print("Czy 0 < a? ");
    System.out.println(GF.toGF(0).less(a) ? "prawda" : "fałsz");

    System.out.print("Czy d < a? ");
    System.out.println(d.less(a) ? "prawda" : "fałsz");

    System.out.println("-------");

    GF e = a.add(b);
    System.out.println("Tworzę e jako a + b : " + e);

    GF f = e.add(GF.toGF(4));
    System.out.println("Tworzę f jako e + 4: " + f);

    GF g = GF.toGF(4).add(e);
    System.out.println("Tworzę g jako 4 + e: " + g);

    GF h = f.add(GF.toGF(-4));
    System.out.println("Tworzę h jako f + (-4): " + h);

    int i = 6 + e.toInt();
    System.out.println("Tworzę int i jako 6 + e: " + i);

    System.out.println("-------");

    h.assign(GF.toGF(-1));
    System.out.println(h);
    System.out.println(h.equals(GF.toGF(-1)) ? "prawda" : "fałsz");

    System.out.println("-------");

    e = a.sub(b);
    System.out.println("e to a - b : " + e);

    f = e.sub(GF.toGF(4));
    System.out.println("f to e - 4: " + f);

    g = GF.toGF(4).sub(f);
    System.out.println("g to 4 - f: " + g);

    h = f.sub(GF.toGF(-1));
    System.out.println("h to f - (-1): " + h);

    f.assign(GF.toGF(5));
    i = 4 - f.toInt();
    System.out.println("int i to 4 - int(f), gdzie f = 5: " + i);

    System.out.println("-------");

    a.assign(GF.toGF(2));
    b.assign(GF.toGF(3));
    c = a.mult(b);
    System.out.println("Dla a = 2, b = 3, c = a * b: " + c);

    d = c.mult(GF.toGF(4));
    System.out.println("d to c * 4: " + d);

    e = GF.toGF(4).mult(c);
    System.out.println("e to 4 * c: " + e);

    i = 4 * c.toInt();
    System.out.println("int i to 4 * c: " + i);

    System.out.println("-------");

    a = c.div(b);
    System.out.println("a to c / b: " + a);

    a = c.div(GF.toGF(3));
    System.out.println("a to c / 3: " + a);

    a = GF.toGF(6).div(b);
    System.out.println("a to 6 / b: " + a);

    i = 18 / a.toInt();
    System.out.println("int i to 18 / a: " + i);

    System.out.println("-------");

    a.assign(GF.toGF(5));
    System.out.println("a to teraz 5");

    a.addTo(a);
    System.out.println("a + a: " + a);

    a.subTo(a);
    System.out.println("a - a: " + a);

    a.subTo(GF.toGF(1));
    System.out.println("a - 1: " + a);

    a.divTo(GF.toGF(2));
    System.out.println("a / 2: " + a);

    a.multTo(GF.toGF(2));
    System.out.println("a * 2: " + a);

    System.out.println("-------");

    GF obj = new GF();
    System.out.print("Podaj wartość dla GF obj: ");
    Scanner scanner = new Scanner(System.in);
    obj.read(scanner);
    System.out.println("Charakterystyka tego obiektu to:");
    obj.about();







  }


}
