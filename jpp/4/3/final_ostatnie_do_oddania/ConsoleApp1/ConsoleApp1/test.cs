using System;

public class test
{
    public static void Main()
    {
        GF dum = new GF();
        DHSetup<GF> dh = new DHSetup<GF>(dum);

        Console.WriteLine("Wspolna liczba pierwsza: " + dum.GetCharacteristic());
        Console.WriteLine("Wspolny generator: " + dh.getGenerator());
        
        GF dupadupa = new GF(3);
        GF dupa = dh.power(dupadupa, 3);
        Console.WriteLine(dupa);

        // tworze user Alice, konstruktor od razu tworzy sekret
        User<GF> Alice = new User<GF>(dh);

        // to samo Bob
        User<GF> Bob = new User<GF>(dh);

        // Alice liczy klucz publiczny
        GF fromAlice = Alice.getPublicKey();
        Console.WriteLine("Klucz od Alice: " + fromAlice);

        // przekazuje do Boba
        Bob.setKey(fromAlice);
        
        // Bob liczy klucz publiczny
        GF fromBob = Bob.getPublicKey();
        Console.WriteLine("Klucz od Boba: " + fromBob);

        // przekazuje do Alice
        Alice.setKey(fromBob);
        
        // Alice koduje wiadomosc
        GF encrypted = Alice.encrypt(new GF(2137));
        Console.WriteLine("Zakodowana wiadomosc: " + encrypted);

        // Bob dekoduje
        GF decrypted = Bob.decrypt(encrypted);
        Console.WriteLine("Odkodowana wiadomosc: " + decrypted);
    }
}
