
import java.util.Random;

public class User<T extends GF> {

    private DHSetup<T> dh;
    private long secret;
    private T key;

    private void setSecret() {
        Random random = new Random();
        long number = random.nextLong(100 - 10) + 10;
        this.secret = number;
        System.out.println("Mój sekret: " + secret);
    }

    public User(DHSetup<T> set) {
        this.dh = set;
        setSecret();
    }

    public T getPublicKey() {
        T ret = dh.power(dh.getGenerator(), secret);
        return ret;
    }

    public void setKey(T a) {
        this.key = dh.power(a, secret);
        System.out.println("Mój klucz: " + key);
    }

    public T encrypt(T m) {
        if (key == null) {
            System.out.println("You cannot encrypt before setting the key!");
            return null;
        } else {
            return (T) m.mult(key);
        }
    }

    public T decrypt(T c) {
        if (key == null) {
            System.out.println("You cannot decrypt before setting the key!");
            return null;
        } else {
            return (T) c.div(key);
        }
    }
}
