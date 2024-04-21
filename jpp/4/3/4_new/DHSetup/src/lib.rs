use rand::Rng;
use GF_mod::GF_trait;
use GF_mod::GF;


pub struct DHSetup<T> {
    generator: T
}

impl<T> DHSetup<T> 
where 
    T: GF_trait
{
    pub fn new() -> Self {
        let generator = Self::generateGenerator();
       // Self {generator}
        println!("konstruktor");
        Self{generator}
    }

    fn generateGenerator() -> T {
        let dum = T::new();
        let chara = T::get_characteristic(dum);

        let number = rand::thread_rng().gen_range(1..chara);
        T::from(number)
    }

    //pub fn getGenerator(&self) -> &T {
    //    &self.generator
    //}

}
