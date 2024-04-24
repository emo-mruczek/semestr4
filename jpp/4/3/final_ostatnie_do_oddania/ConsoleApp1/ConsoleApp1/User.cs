using System;

public class User<T> where T: GF, new()
{
    private DHSetup<T> dh;
    private ulong secret;
    private T key;
    
    private void setSecret() {
        Random random = new Random();
        ulong number = (ulong)random.Next(10, 100);
        this.secret = number;
        Console.WriteLine("Mój sekret: " + secret); 
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
        Console.WriteLine("Mój klucz: " + key);
    }
    
    public T encrypt(T m) {
        if (key is null) {
            Console.WriteLine("You cannot encrypt before setting the key!");
            return null;
        } else
       {
            return (T) (m * key);
        }
    }

    public T decrypt(T c) {
        if (key is null) {
            Console.WriteLine("You cannot decrypt before setting the key!");
            return null;
        } else {
            return (T) (c/key);
        }
    }
}
