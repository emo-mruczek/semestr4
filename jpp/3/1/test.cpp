#include <iostream>
#include "GF.hpp"

using namespace std;

int main() {

    //sprawdz podstawianie za duzych wartosci!
    //zapytaj sie jacka o dzielenie
    //zmien porownania

    cout << "Tworzę dwa obiekty: a i b" << endl;
    GF a;
    GF b;

    cout << "Ich obecne wartości to: a: " << a << " b: " << b << endl;

    a = GF(22);
    cout << "Podstawiam za a wartosc 22: a: " << a << endl;

    b = a;
    cout << "Podstawiam a do b: b: " << b << endl;

    cout << "-------" << endl;

    cout << "Czy a == b? ";
    cout << ((a == b) ? "prawda\n" : "fałsz\n");

    cout << "Czy a == 1? ";
    cout << ((a == GF(1)) ? "prawda\n" : "fałsz\n");

    cout << "Czy a == 22? ";
    cout << ((a == GF(22)) ? "prawda\n" : "fałsz\n");

    cout << "Czy a == 3? ";
    cout << ((a == GF(3)) ? "prawda\n" : "fałsz\n");

    cout << "-------" << endl;

    cout << "Czy a != b? ";
    cout << ((a != b) ? "prawda\n" : "fałsz\n");

    cout << "Czy a != 1? ";
    cout << ((a != GF(1)) ? "prawda\n" : "fałsz\n");

    cout << "Czy a != 22? ";
    cout << ((a != GF(22)) ? "prawda\n" : "fałsz\n");

    cout << "Czy a != 3? ";
    cout << ((a != GF(3)) ? "prawda\n" : "fałsz\n");

    cout << "-------" << endl;

    GF c = GF(12);
    GF d = GF(0);

    cout << "Tworzę c: " << c << " i d: " << d << endl;

    cout << "Czy a <= c? ";
    cout << ((a <= c) ? "prawda\n" : "fałsz\n");

    cout << "Czy a > c? ";
    cout << ((a > c) ? "prawda\n" : "fałsz\n");

    cout << "Czy a < 12? ";
    cout << ((a < GF(12)) ? "prawda\n" : "fałsz\n");

    cout << "Czy a < d? ";
    cout << ((a < d) ? "prawda\n" : "fałsz\n");

    cout << "Czy 0 < a? ";
    cout << ((GF(0) < a) ? "prawda\n" : "fałsz\n");

    cout << "Czy d < a? ";
    cout << ((d < a) ? "prawda\n" : "fałsz\n");

    cout << "-------" << endl;

    GF e = a + b;
    cout << "Tworzę e jako a + b : " << e << endl;

    GF f = e + GF(4);
    cout << "Tworzę f jako e + 4: " << f << endl;

    GF g = GF(4) + e;
    cout << "Tworzę g jako 4 + e: " << g << endl;

    GF h =  f + GF((-4));
    cout << "Tworzę h jako f + (-4): " << h << endl;

    int i = 6 + int(e);
    cout << "Tworzę int i jako 6 + e: " << i << endl;
    

    cout << "-------" << endl;

    h = GF(-1);
    cout << h << endl;

    cout << ((h == GF(-1)) ? "prawda\n" : "fałsz\n");

    cout << "-------" << endl;

    e = a - b;
    cout << "e to a - b : " << e << endl;

    f = e - GF(4);
    cout << "f to e - 4: " << f << endl;

    g = GF(4) - f;
    cout << "g to 4 - f: " << g << endl;

    h = f - GF((-1));
    cout << "h to f - (-1): " << h << endl;

    f = GF(5);
    i = 4 - int(f);
    cout << "int i to 4 - int(f): " << i << endl;

    cout << "-------" << endl;

    a = GF(2);
    b = GF(3);
    c = a * b;
    cout << "Dla a = 2, b = 3, c = a * b: " << c << endl;

    d = c * GF(4);
    cout << "d to c * 4: " << d << endl;

    e = GF(4) * c;
    cout << "e to 4 * c: " << e << endl;

    i = 4 * int(c);
    cout << "int i to 4 * c: " << i << endl;

    cout << "-------" << endl;

    a = c / b;
    cout << "a to c / b: " << a << endl;

    a = c * GF(3);
    cout << "a to c / 3: " << a << endl;

    a = GF(6) * b;
    cout << "a to 6 / b: " << a << endl;

    i = 18 / int(a);
    cout << "int i to 18 / a: " << i << endl;

    cout << "-------" << endl;

    a = GF(5);
    a += a;
    cout << "a to teraz 5" << endl;
    cout << "a + a: " << a << endl;

    a -= a;
    cout << "a - a: " << a << endl;

    a -= GF(1);
    cout << "a - 1: " << a << endl;

    a /= GF(2);
    cout << "a / 2: " << a << endl;

    a *= GF(2);
    cout << "a * 2: " << a << endl;













}