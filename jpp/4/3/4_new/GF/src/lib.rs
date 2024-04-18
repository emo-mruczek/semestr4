use std::cmp::Ordering;
use std::ops::Add;
use std::ops::Sub;
use std::ops::Mul;
use std::ops::Div;
use std::fmt;
use std::str::FromStr;

#[derive(Clone, Copy)]
pub struct GF {
    size: i64,
    value: i64,
}

impl GF {

    //kontruktor
    pub fn new() -> Self{
        GF {
            size: 1234567891,
            value: 0,
        }
    }

     pub fn from(n: i64) -> Self {
        let size: i64 = 1234567891;
        let value: i64 = if n >= 0 {
            n as i64 % size
        } else {
            (size - (n * (-1))) % size
        };
        GF { size, value }
    }

    // konwersja
    pub fn to_u64(&self) -> i64 {
        self.value
    }

    // do zwracania charakterystyki
    pub fn get_characteristic(&self) -> i64 {
        self.size
    }

     pub fn clone_from(&mut self, other: &GF) {
        if self as *const _ != other as *const _ {
            self.value = other.value;
        }
    }

     pub fn add_assign(&mut self, other: Self) {
        self.value = (self.value + other.value) % self.size;
    }

    // -=
    pub fn sub_assign(&mut self, other: Self) {
        self.value = (self.value - other.value + self.size) % self.size;
    }

    // *=
    pub fn mul_assign(&mut self, other: Self) {
        self.value = (self.value * other.value) % self.size;
    }

    // /=
    pub fn div_assign(&mut self, other: Self) {
        if other.value == 0 {
            panic!("Division by zero");
        }

        let mut inverse = 1;
        for i in 1..self.size {
            if (other.value * i) % self.size == 1 {
                inverse = i;
                break;
            }
        }

        self.value = (self.value * inverse) % self.size;
    }

}


// do porownan; duzo sie dzieje dzieki Ordering

impl Eq for GF{}

impl PartialEq for GF {
    fn eq(&self, other: &Self) -> bool {
        self.value == other.value
    }
}

impl PartialOrd for GF {
    fn partial_cmp(&self, other:&Self) -> Option<Ordering> {
        Some(self.value.cmp(&other.value))
    }
}

impl Ord for GF {
    fn cmp(&self, other: &Self) -> Ordering {
        self.value.cmp(&other.value)
    }
}

impl Add for GF {
    type Output = Self;

    fn add(self, other: Self) -> Self {
        let mut res = GF::new();
        res.value = (self.value + other.value) % self.size;
        res
    }
}

impl Sub for GF {
    type Output = Self;

    fn sub(self, other: Self) -> Self {
        let mut res = GF::new();
        res.value = (self.value - other.value + self.size) % self.size;
        res
    }
}

impl Mul for GF {
    type Output = Self;

    fn mul(self, other: Self) -> Self {
        let mut res = GF::new();
        res.value = (self.value * other.value) % self.size;
        res
    }
}

impl Div for GF {
    type Output = Self;

    fn div(self, other: Self) -> Self {
        if other.value == 0 {
            panic!("Division by zero");
        }

        let mut inverse = 1;
        for i in 1..self.size {
            if (other.value * i) % self.size == 1 {
                inverse = i;
                break;
            }
        }

        let mut res = GF::new();
        res.value = (self.value * inverse) % self.size;
        res
    }
}




