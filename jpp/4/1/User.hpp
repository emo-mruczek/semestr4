
// NIE MAM POJEIA CZY TO DZIALA, PISANE NA KRZYWY RYJ

#include <cstdint>
#include <random>

template <typename T>
class User {

// TODO: dodaj sygnalizowanie niewlasciwego uzycia metod

    private:

    DHSetup dh;

    uint64_t secret;

    T key;

    void setSecret() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(10, 100); // jak duzy powinienen byc ten sekret maksymalnie??
        uint64_t number = distr(gen);

        secret = number;
    }

    public:

    User(&DHSetup set){
        this->dh = set;
        setSecret();
        cin << secret;
    }

    T getPublicKey() {
        T ret = dh.power(dh.getGenerator, secret);
        return ret;
    }

    void setKey(T a) {
        this->key = dh.power(a, secret);
    }

    T encrypt(T m) {
        m *= key;
        return m;
    }

    T decrypt(T c) {
        c /= key;
        return c;
    }
};
