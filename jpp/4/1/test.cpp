#include <iostream>
#include "DHSetup.hpp"
#include "GF.hpp"

int main() {
    
    GF gf;
    DHSetup dh = DHSetup(gf);

    return 0;
}
