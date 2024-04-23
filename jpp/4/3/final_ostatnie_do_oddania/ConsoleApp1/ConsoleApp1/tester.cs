namespace ConsoleApp1;

public class tester
{
   


    public static void Mainjjdfd()
    {
        Console.WriteLine("Tworzę dwa obiekty: a i b");
        GF a = new GF();
        GF b = new GF();

        Console.WriteLine("Ich obecne wartości to: a: " + (int)a + " b: " + (int)b);

        a = new GF(22);
        Console.WriteLine("Podstawiam za a wartosc 22: a: " + (int)a);

        b = a;
        Console.WriteLine("Podstawiam a do b: b: " + (int)b);

        Console.WriteLine("-------");
   
        Console.Write("Czy a == b? ");
        Console.WriteLine(a == b);

        Console.Write("Is a == 1? ");
        Console.WriteLine(a == new GF(1));

        Console.Write("Is a == 22? ");
        Console.WriteLine(a == new GF(22));

        Console.Write("Is a == 3? ");
        Console.WriteLine(a == new GF(3));

        Console.WriteLine("-------");

        Console.Write("Is a != b? ");
        Console.WriteLine(a != b);

        Console.Write("Is a != 1? ");
        Console.WriteLine(a != new GF(1));

        Console.Write("Is a != 22? ");
        Console.WriteLine(a != new GF(22));

        Console.Write("Is a != 3? ");
        Console.WriteLine(a != new GF(3));

        Console.WriteLine("-------");

        GF c = new GF(12);
        GF d = new GF(0);
        
        Console.WriteLine("Creating c: " + (int)c + " and d: " + (int)d);

        Console.Write("Is a <= c? ");
        Console.WriteLine(a <= c);

        Console.Write("Is a > c? ");
        Console.WriteLine(a > c);

        Console.Write("Is a < 12? ");
        Console.WriteLine(a < new GF(12));

        Console.Write("Is a < d? ");
        Console.WriteLine(a < d);

        Console.Write("Is 0 < a? ");
        Console.WriteLine(new GF(0) < a);

        Console.Write("Is d < a? ");
        Console.WriteLine(d < a);
        
        Console.WriteLine("-------");
        
        GF e = a + b;
        Console.WriteLine("Creating e as a + b: " + (int)e);

        GF f = e + new GF(4);
        Console.WriteLine("Creating f as e + 4: " + (int)f);

        GF g = new GF(4) + e;
        Console.WriteLine("Creating g as 4 + e: " + (int)g);

        GF h = f + new GF(-4);
        Console.WriteLine("Creating h as f + (-4): " + (int)h);

        int i = 6 + (int)e;
        Console.WriteLine("Creating int i as 6 + e: " + i);
        
        Console.WriteLine("-------");

        h = new GF(-1);
        Console.WriteLine("h: " + (int)h);
        Console.WriteLine((h == new GF(-1)) ? "true" : "false");

        Console.WriteLine("-------");
        
        e = a - b;
        Console.WriteLine("e as a - b: " + (int)e);

        f = e - new GF(4);
        Console.WriteLine("f as e - 4: " + (int)f);

        g = new GF(4) - f;
        Console.WriteLine("g as 4 - f: " + (int)g);

        h = f - new GF(-1);
        Console.WriteLine("h as f - (-1): " + (int)h);

        f = new GF(5);
        i = 4 - (int)f;
        Console.WriteLine("int i as 4 - int(f): " + i);
        
        Console.WriteLine("-------");
        
        a = new GF(2);
        b = new GF(3);
        c = a * b;
        Console.WriteLine("For a = 2, b = 3, c as a * b: " + (int)c);

        d = c * new GF(4);
        Console.WriteLine("d as c * 4: " + (int)d);

        e = new GF(4) * c;
        Console.WriteLine("e as 4 * c: " + (int)e);

        i = 4 * (int)c;
        Console.WriteLine("int i as 4 * c: " + i);
        
        Console.WriteLine("-------");
        
        a = c / b;
        Console.WriteLine("a as c / b: " + (int)a);

        a = c * new GF(3);
        Console.WriteLine("a as c * 3: " + (int)a);

        a = new GF(6) * b;
        Console.WriteLine("a as 6 * b: " + (int)a);

        i = 18 / (int)a;
        Console.WriteLine("int i as 18 / a: " + i);

        Console.WriteLine("-------");    
        
        a = new GF(5);
        Console.WriteLine("-------");

        a += a;
        Console.WriteLine("a is now 5");
        Console.WriteLine("a + a: " + a);

        a -= a;
        Console.WriteLine("a - a: " + a);

        a -= new GF(1);
        Console.WriteLine("a - 1: " + a);

        a /= new GF(2);
        Console.WriteLine("a / 2: " + a);

        a *= new GF(2);
        Console.WriteLine("a * 2: " + a);

        Console.WriteLine("-------");
        
    }
}
