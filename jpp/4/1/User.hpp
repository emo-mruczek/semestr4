
// NIE MAM POJEIA CZY TO DZIALA, PISANE NA KRZYWY RYJ

#include <cstdint>
#include <random>

template <typename T>
class User {

// TODO: dodaj sygnalizowanie niewlasciwego uzycia metod

    private:

    DHSetup<T> dh;

    uint64_t secret;

    T key = T(0);

    void setSecret() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(10, 100); // jak duzy powinienen byc ten sekret maksymalnie??
        uint64_t number = distr(gen);

        secret = number;
    }

    public:

    User(DHSetup<T>& set){
        this->dh = set;
        setSecret();
        std::cout << "Moj sekret: " << secret << std::endl;
    }

    T getPublicKey() {
        T ret = dh.power(dh.getGenerator(), secret);
        return ret;
    }

    void setKey(T a) {
        this->key = dh.power(a, secret);
        std::cout << "Moj klucz: " << key << std::endl;
    }

    T encrypt(T m) {
        if (key == T(0)) {
                std::cout << "You cannot encrypt before setting the key!";
                return T(0);
        } else {
            m *= key;
            return m;
        }
    }

    T decrypt(T c) {
        if (key == T(0)) {
                std::cout << "You cannot encrypt before setting the key!";
                return T(0);
        } else {
        c /= key;
        return c;
        }
    }
};
