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





    return 0;
}
