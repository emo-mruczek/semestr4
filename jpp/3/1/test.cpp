#include <iostream>
#include "GF.hpp"

using namespace std;

int main() {

    //sprawdz podstawianie za duzych wartosci!

    cout << "Tworzę dwa obiekty: a i b" << endl;
    GF a;
    GF b;

    cout << "Ich obecne wartości to: a: " << a << " b: " << b << endl;

    a = 22;
    cout << "Podstawiam za a wartosc 22: a: " << a << endl;

    b = a;
    cout << "Podstawiam a do b: b: " << b << endl;

    cout << "Czy a == b? ";
    cout << ((a == b) ? "prawda\n" : "fałsz\n");

    cout << "Czy a == 1? ";
    cout << ((a == 1) ? "prawda\n" : "fałsz\n");

    cout << "Czy a == 22? ";
    cout << ((a == 22) ? "prawda\n" : "fałsz\n");

    cout << "Czy a == 3? ";
    cout << ((a == 3) ? "prawda\n" : "fałsz\n");

    cout << "Czy 1 == a? ";
    cout << ((1 == a) ? "prawda\n" : "fałsz\n");

    cout << "Czy 3 == a? ";
    cout << ((3 == a) ? "prawda\n" : "fałsz\n");

    cout << "-------" << endl;

    cout << "Czy a != b? ";
    cout << ((a != b) ? "prawda\n" : "fałsz\n");

    cout << "Czy a != 1? ";
    cout << ((a != 1) ? "prawda\n" : "fałsz\n");

    cout << "Czy a != 22? ";
    cout << ((a != 22) ? "prawda\n" : "fałsz\n");

    cout << "Czy a != 3? ";
    cout << ((a != 3) ? "prawda\n" : "fałsz\n");

    cout << "Czy 1 != a? ";
    cout << ((1 != a) ? "prawda\n" : "fałsz\n");

    cout << "Czy 3 != a? ";
    cout << ((3 != a) ? "prawda\n" : "fałsz\n");

    cout << "-------" << endl;

    GF c = 12;
    GF d = 0;

    cout << "Tworzę c: " << c << " i d: " << d << endl;

     cout << "Czy a <= c? ";
    cout << ((a <= c) ? "prawda\n" : "fałsz\n");

    cout << "Czy a > c? ";
    cout << ((a > c) ? "prawda\n" : "fałsz\n");

    cout << "Czy a < 12? ";
    cout << ((a < 22) ? "prawda\n" : "fałsz\n");

    cout << "Czy a < d? ";
    cout << ((a < d) ? "prawda\n" : "fałsz\n");

    cout << "Czy 0 < a? ";
    cout << ((0 < a) ? "prawda\n" : "fałsz\n");

    cout << "Czy d < a? ";
    cout << ((d < a) ? "prawda\n" : "fałsz\n");




}