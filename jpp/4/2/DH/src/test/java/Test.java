import org.example.DHSetup;
import org.example.GF;
import org.example.User;

public class Test {
  public static void main(String[] args) {
    GF dum = new GF();
    DHSetup<GF> dh = new DHSetup<>(dum);
    System.out.println("Wspolna liczba pierwsza: " + dum.getCharacteristic());
    System.out.println("Wspolny generator: " + dh.getGenerator());

    // tworze user Alice, konstruktor od razu tworzy sekret
    User<GF> Alice = new User<>(dh);

    // to samo Bob
    User<GF> Bob = new User<>(dh);

    // Alice liczy klucz publiczny
    GF fromAlice = Alice.getPublicKey();
    System.out.println("Klucz od Alice: " + fromAlice);

    // przekazuje do Boba
    Bob.setKey(fromAlice);

    // Bob liczy klucz publiczny
    GF fromBob = Bob.getPublicKey();
    System.out.println("Klucz od Boba: " + fromBob);

    // przekazuje do Alice
    Alice.setKey(fromBob);

    // Alice koduje wiadomosc
    GF encrypted = Alice.encrypt(new GF(2137));
    System.out.println("Zakodowana wiadomosc: " + encrypted);

    // Bob dekoduje
    GF decrypted = Bob.decrypt(encrypted);
    System.out.println("Odkodowana wiadomosc: " + decrypted);

  }
}
