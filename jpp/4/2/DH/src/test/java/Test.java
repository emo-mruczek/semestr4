import org.example.DHSetup;
import org.example.GF;

public class Test {
  public static void main(String[] args) {
    GF dum = new GF();
    DHSetup<GF> dh = new DHSetup<>(dum);
    System.out.println("Wspolna liczba pierwsza: " + dum.getCharacteristic());
    System.out.println("Wspolny generator: " + dh.getGenerator());


  }
}
