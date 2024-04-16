#include <iostream>
#include "DHSetup.hpp"
#include "GF.hpp"
#include "User.hpp"

int main() {
    
    // init
    // nasze gf jest liczba pierwsza 1234567891 (p), generator jest stworzony w DHSetup (g)
    GF dum;
    DHSetup<GF> dh;
    std::cout << "Wspolna liczba pierwsza: " << dum.getCharacteristic() << std::endl;
    std::cout << "Wspolny generator: " << dh.getGenerator() << std::endl;

    // tworze user Alice, konstruktor od razu tworzy sekret 
    User<GF> Alice(dh);

    // to samo Bob
    User<GF> Bob(dh);

    // Alice liczy klucz publiczny
    GF fromAlice = Alice.getPublicKey();
    std::cout << "Klucz od Alice: " << fromAlice << std::endl;

    // przekazuje do Boba
    Bob.setKey(fromAlice);

    // Bob liczy klucz publiczny
    GF fromBob = Bob.getPublicKey();
    std::cout << "Klucz od Boba: " << fromBob << std::endl;

    // przekazuje do Alice
    Alice.setKey(fromBob);

    // Alice koduje wiadomosc
    GF encrypted = Alice.encrypt(GF(2137));
    std::cout << "Zakodowana wiadomosc: " << encrypted << std::endl;

    // Bob dekoduje
    GF decrypted = Bob.decrypt(encrypted);
    std::cout << "Odkodowana wiadomosc: " << decrypted << std::endl;





    return 0;
}
