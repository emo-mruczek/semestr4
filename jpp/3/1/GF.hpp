#include <iostream>

class GF {
    private:

    unsigned int size = 21;

    unsigned int value;

    unsigned int convert(unsigned int n) {
        return n % size;
    }

    public:

    GF() {
        value = 0;
    }

    GF& operator=(const GF& obj) {
        if (this != &obj) {
            this->value = obj.value;
        }
        return *this;
    }

    GF& operator=(unsigned int n) {
        this->value = this->convert(n);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, GF obj) {
        return os << obj.value;
    }

};