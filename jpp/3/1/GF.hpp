#include <iostream>

class GF {
    private:

    unsigned int size = 21;

    unsigned int value;

    public:

    // konstruktor
    GF() {
        value = 0;
    }

    GF(unsigned int n ) {
        value = n % size;
    }

    // operatory porównań
    // ==
    friend bool operator==(const GF& obj_a, const GF& obj_b) {
        return (obj_a.value == obj_b.value) ? true : false;
    }

    friend bool operator==(const GF& obj_a, unsigned int n) {
        return (obj_a.value == n % obj_a.size) ? true : false;
    }

    friend bool operator==(unsigned int n, const GF& obj_a) {
        return (obj_a.value == n % obj_a.size) ? true : false;
    }

    // !=
     friend bool operator!=(const GF& obj_a, const GF& obj_b) {
        return (obj_a.value != obj_b.value) ? true : false;
    }

    friend bool operator!=(const GF& obj_a, unsigned int n) {
        return (obj_a.value != n % obj_a.size) ? true : false;
    }

    friend bool operator!=(unsigned int n, const GF& obj_a) {
        return (obj_a.value != n % obj_a.size) ? true : false;
    }

    // <=
    friend bool operator<=(const GF& obj_a, const GF& obj_b) {
        return (obj_a.value <= obj_b.value) ? true : false;
    }

    friend bool operator<=(const GF& obj_a, unsigned int n) {
        return (obj_a.value <= n % obj_a.size) ? true : false;
    }

    friend bool operator<=(unsigned int n, const GF& obj_a) {
        return (n % obj_a.size <= obj_a.value  ) ? true : false;
    }

    // >=
    friend bool operator>=(const GF& obj_a, const GF& obj_b) {
        return (obj_a.value >= obj_b.value) ? true : false;
    }

    friend bool operator>=(const GF& obj_a, unsigned int n) {
        return (obj_a.value >= n % obj_a.size) ? true : false;
    }

    friend bool operator>=(unsigned int n, const GF& obj_a) {
        return (n % obj_a.size >= obj_a.value ) ? true : false;
    }

     // <
    friend bool operator<(const GF& obj_a, const GF& obj_b) {
        return (obj_a.value < obj_b.value) ? true : false;
    }

    friend bool operator<(const GF& obj_a, unsigned int n) {
        return (obj_a.value < n % obj_a.size) ? true : false;
    }

    friend bool operator<(unsigned int n, const GF& obj_a) {
       return (n % obj_a.size < obj_a.value ) ? true : false;
    }

    // >
    friend bool operator>(const GF& obj_a, const GF& obj_b) {
        return (obj_a.value > obj_b.value) ? true : false;
    }

    friend bool operator>(const GF& obj_a, unsigned int n) {
        return (obj_a.value > n % obj_a.size) ? true : false;
    }

    friend bool operator>(unsigned int n, const GF& obj_a) {
        return (n % obj_a.size > obj_a.value ) ? true : false;
    }

    // operatory arytmetyczne
    



    // operatory podstawień
    // przypisanie
    GF& operator=(const GF& obj) {
        if (this != &obj) {
            this->value = obj.value;
        }
        return *this;
    }

    GF& operator=(unsigned int n) {
        this->value = n % size;
        return *this;
    }

    // streamy
    friend std::ostream& operator<<(std::ostream& os, GF obj) {
        return os << obj.value;
    }

};