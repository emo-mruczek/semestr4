use rand::Rng;
use GF::GF;

pub trait GF {
    fn get_characteristic() -> i64;
    fn from(n: i64) -> Self;
}

pub struct DHSetup<T: GF> {
    generator: T
}

impl<T: GF> DHSetup<T> {
    pub fn new() -> Self {
        let generator = Self::generateGenerator();
        Self {generator}
    }

    fn generateGenerator() -> T {
        let chara = T::get_characteristic();
        let number = rand::thread_rng().gen_range(1..chara);
        T::from(number)
    }

    //pub fn getGenerator(&self) -> &T {
    //    &self.generator
    //}

}
