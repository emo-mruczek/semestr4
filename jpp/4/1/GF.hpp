#include <iostream>
#include <cstdint>


class GF {

    // TODO:
    //zeby int mial zawszze 32

    //scanner dla -1!!!!

    private:

    uint64_t size = 1234567891;

    uint64_t value;

    public:

    // konstruktor
    GF() {
        value = 0;
    }

    // tez do konwersji int na GF
    GF(uint64_t n) {
        if (n >= 0) {
            value = n % size;
        } else {
            value = ((size - (-n)) % size);
        }
    }

    // konwersja na int
    operator int() const {
        return value;
    }

    // do zwracania charakterystyki
    int getCharacteristic() {
        return size;
    }


    // operatory porównań
    // ==
    friend bool operator==(const GF& obj_a, const GF& obj_b) {
        return obj_a.value == obj_b.value;
    }

    // !=
    friend bool operator!=(const GF& obj_a, const GF& obj_b) {
        return obj_a.value != obj_b.value;
    }

    // <=
    friend bool operator<=(const GF& obj_a, const GF& obj_b) {
        return obj_a.value <= obj_b.value;
    }

    // >=
    friend bool operator>=(const GF& obj_a, const GF& obj_b) {
        return obj_a.value >= obj_b.value;
    }

     // <
    friend bool operator<(const GF& obj_a, const GF& obj_b) {
        return obj_a.value < obj_b.value;
    }

    // >
    friend bool operator>(const GF& obj_a, const GF& obj_b) {
        return obj_a.value > obj_b.value;
    }

    // operatory arytmetyczne
    // +
    GF operator+(const GF& obj) const {
       /* if (this->size != obj.size) {
           throw std::runtime_error("Incompatible types");
        }*/

        GF res;
        res.value = (this->value + obj.value) % this->size;
        return res;
    }

    // -
    GF operator-(const GF& obj) const {
       /* if (this->size != obj.size) {
           throw std::runtime_error("Incompatible types");
        }*/

        GF res;
        res.value = (this->value - obj.value + this->size) % this->size;
        return res;
    }

    // *
    GF operator*(const GF& obj) const {
        /*if (this->size != obj.size) {
           throw std::runtime_error("Incompatible types");
        }*/

        GF res;
        res.value = (this->value * obj.value) % this->size;
        return res;
    }

    // /
    GF operator/(const GF& obj) const {
       /* if (this->size != obj.size) {
           throw std::runtime_error("Incompatible types");
        }*/

        if (obj.value == 0) {
        throw std::runtime_error("Division by zero");
        }

        unsigned int inverse = 1;
        for (unsigned int i = 1; i < this->size; i++) {
            if ((obj.value * i) % this->size == 1) {
                inverse = i;
                break;
            }
        }
    
        GF res;
        res.value = (this->value * inverse) % this->size;
        return res;
    }

    // operatory podstawień
    // =
    GF& operator=(const GF& obj) {
        if (this != &obj) {
            this->value = obj.value;
        }
        return *this;
    }

    GF& operator=(int n) {
        throw std::runtime_error("You can't put int as GF!"); // musi byc konwersja!
    }

    // +=
    GF& operator+=(const GF& obj) {
        /* if (this->size != obj.size) {
           throw std::runtime_error("Incompatible types");
        }*/

        this->value = (this->value + obj.value) % this->size;
        return *this;
    }

    GF& operator+=(int n) {
        throw std::runtime_error("You can't put int as GF!"); // musi byc konwersja!
    }

    // -=
    GF& operator-=(const GF& obj) {
        /* if (this->size != obj.size) {
           throw std::runtime_error("Incompatible types");
        }*/

        this->value = (this->value - obj.value + this->size) % this->size;
        return *this;
    }

    GF& operator-=(int n) {
        throw std::runtime_error("You can't put int as GF!"); // musi byc konwersja!
    }

    // *=
    GF& operator*=(const GF& obj) {
        /*if (this->size != obj.size) {
           throw std::runtime_error("Incompatible types");
        }*/ 

        this->value = (this->value * obj.value) % this->size;
        return *this;
    }

    GF& operator*=(int n) {
        throw std::runtime_error("You can't put int as GF!"); // musi byc konwersja!
    }

    // /=
    GF& operator/=(const GF& obj) {
       /*  if (this->size != obj.size) {
           throw std::runtime_error("Incompatible types");
        }*/

        if (obj.value == 0) {
        throw std::runtime_error("Division by zero");
        }

        unsigned int inverse = 1;
        for (unsigned int i = 1; i < this->size; ++i) {
        if ((obj.value * i) % this->size == 1) {
            inverse = i;
            break;
            }
        }

        this->value = (this->value * inverse) % this->size;
        return *this;
    }

    GF& operator/=(int n) {
        throw std::runtime_error("You can't put int as GF!"); // musi byc konwersja!
    }

    // streamy
    friend std::ostream& operator<<(std::ostream& os, const GF& obj) {
        return os << obj.value;
    }

    friend std::istream& operator>>(std::istream& is, GF& obj) {
        int temp;
        is >> temp;
        obj.value = temp % obj.size;
        return is;
    }

};
