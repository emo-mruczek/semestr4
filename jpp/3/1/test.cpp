#include <iostream>
#include "GF.hpp"

using namespace std;

int main() {

    //sprawdz podstawianie za duzych wartosci!

    cout << "Tworzę dwa obiekty: a i b" << endl;
    GF a;
    GF b;

    cout << "Ich obecne wartości to: a - " << a << " b - " << b << endl;

    a = 22;
    cout << "Podstawiam za a wartosc 22: a - " << a << endl;

    b = a;
    cout << "Podstawiam b do a: b - " << b << endl;


}