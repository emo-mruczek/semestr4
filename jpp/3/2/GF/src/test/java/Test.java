import org.example.GF;

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



  }


}
