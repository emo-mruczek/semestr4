#include <random>

template <typename T>
class DHSetup {
    private:
    
    int generator;

    // dla liczby pierwszej, funkcja fi eulera fi(p) = p - 1, wiec jest tyle elementow odwracalnych, czyli
    // są to elementy od 1 do p-1, czyli moge losowac od 1 do p-1 i bedzie git
    int generateGenerator(T field) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(1, field.getCharacteristic());
        
        return distr(gen);
    }

    

    public: 

    DHSetup(T field) {
        this->generator = generateGenerator(field);
        int chara = field.getCharacteristic();
        std::cout << chara << std::endl;
        std::cout << this->generator << std::endl;
    }


};
