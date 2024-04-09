#include <iostream>

class GF {

    //scanner dla -1!!!!

    private:

    int size = 1234577;

    int value;

    public:

    // konstruktor
    GF() {
        value = 0;
    }

    // tez do konwersji int na GF
    GF(int n) {
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
    void about() {
        std::cout << "Size: " << this->size << " Value: " << this->value << std::endl;
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
        if (temp >= 0) {
            obj.value = temp % obj.size;
        } else {
            obj.value = ((obj.size - (-temp)) % obj.size);
        }
        return is;
    }

};
