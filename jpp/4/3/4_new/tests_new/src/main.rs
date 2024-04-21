use GF::GF;
use DHSetup::DHSetup;

fn main() {
    let dum = GF::new();
    let dh: DHSetup<GF> = DHSetup::new();

    //println!("Wspolna liczba pierwsza: {}", dum.get_characteristic());
  //  println!("Wspolny generator: {}", dh.getGenerator());
}
