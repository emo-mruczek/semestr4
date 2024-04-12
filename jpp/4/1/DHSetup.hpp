#include <random>
#include <cstdint>

template <typename T>
class DHSetup {
    private:
    
    T generator;

    // dla liczby pierwszej, funkcja fi eulera fi(p) = p - 1, wiec jest tyle elementow odwracalnych, czyli
    // są to elementy od 1 do p-1, czyli moge losowac od 1 do p-1 i bedzie git
    T generateGenerator(T field) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(1, field.getCharacteristic());
        uint64_t number = distr(gen);

        return T(number);
    }

    public: 

    DHSetup(T field) {
        this->generator = generateGenerator(field);
        int chara = field.getCharacteristic();
        std::cout << chara << std::endl;
        std::cout << this->generator << std::endl;
    }

    T getGenerator() {
        return generator;
    }

    T power(T a, uint64_t b) {
        T temp;
        if (b == 0) {
            return 1; // czy to jest prawda??
        } 

        temp = power(a, b / 2);
        if (b % 2 == 0) {
            return temp * temp;
        } else {
            return a * temp * temp;
        }
    }
};
