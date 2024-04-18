
use GF::GF;
use std::cmp::Ordering;

fn main() {
    let mut a = GF::new();
    let mut b = GF::new();

    println!("Tworzę dwa obiekty: a i b");
    println!("Ich obecne wartości to: a: {}, b: {}", a.to_u64(), b.to_u64());

    a = GF::from(22);
    println!("Podstawiam za a wartość 22: a: {}", a.to_u64());

    b.clone_from(&a);
    println!("Podstawiam a do b: b: {}", b.to_u64());

    println!("-------");

    println!("Czy a == b? {}", a == b);
    println!("Czy a == 1? {}", a == GF::from(1));
    println!("Czy a == 22? {}", a == GF::from(22));
    println!("Czy a == 3? {}", a == GF::from(3));

    println!("-------");

    println!("Czy a != b? {}", a != b);
    println!("Czy a != 1? {}", a != GF::from(1));
    println!("Czy a != 22? {}", a != GF::from(22));
    println!("Czy a != 3? {}", a != GF::from(3));

    println!("-------");

    let mut c = GF::from(12);
    let mut d = GF::from(0);

    println!("Tworzę c: {} i d: {}", c.to_u64(), d.to_u64());

    println!("Czy a <= c? {}", if a <= c { "prawda" } else { "fałsz" });
    println!("Czy a > c? {}", if a > c { "prawda" } else { "fałsz" });
    println!("Czy a < 12? {}", if a < GF::from(12) { "prawda" } else { "fałsz" });
    println!("Czy a < d? {}", if a < d { "prawda" } else { "fałsz" });
    println!("Czy 0 < a? {}", if GF::from(0) < a { "prawda" } else { "fałsz" });
    println!("Czy d < a? {}", if d < a { "prawda" } else { "fałsz" });

    println!("-------");

     let mut e = a + b;
    println!("Tworzę e jako a + b : {}", e.to_u64());

    let mut f = e + GF::from(4);
    println!("Tworzę f jako e + 4: {}", f.to_u64());

    let mut g = GF::from(4) + e;
    println!("Tworzę g jako 4 + e: {}", g.to_u64());

    let mut h = f + GF::from(-4);
    println!("Tworzę h jako f + (-4): {}", h.to_u64());

    let mut i = 6 + e.to_u64();
    println!("Tworzę int i jako 6 + e: {}", i);

    println!("-------");

    let h = GF::from(-1);
    println!("{}", h.to_u64());

    println!("{}", if h == GF::from(-1) { "prawda" } else { "fałsz" });

    println!("-------");

    let a = GF::from(10);
    let b = GF::from(5);

    let e = a - b;
    println!("e to a - b : {}", e.to_u64());

    let f = e - GF::from(4);
    println!("f to e - 4: {}", f.to_u64());

    let g = GF::from(4) - f;
    println!("g to 4 - f: {}", g.to_u64());

    let h = f - GF::from(-1);
    println!("h to f - (-1): {}", h.to_u64());

    let f = GF::from(5);
    let i = 4 - f.to_u64();
    println!("int i to 4 - int(f): {}", i);

    println!("-------");

    let a = GF::from(2);
    let b = GF::from(3);

    let c = a * b;
    println!("Dla a = 2, b = 3, c = a * b: {}", c.to_u64());

    let d = c * GF::from(4);
    println!("d to c * 4: {}", d.to_u64());

    let e = GF::from(4) * c;
    println!("e to 4 * c: {}", e.to_u64());

    let i = 4 * c.to_u64();
    println!("int i to 4 * c: {}", i);

    println!("-------");

    let c = GF::from(10);
    let b = GF::from(5);

 //   let a = c / b;
    println!("a to c / b: {}", a.to_u64());

  //  let a = c / GF::from(3);
    println!("a to c / 3: {}", a.to_u64());

  //  let a = GF::from(6) / b;
    println!("a to 6 / b: {}", a.to_u64());

   // let i = 18 / a.to_u64();
    println!("int i to 18 / a: {}", i);

    println!("-------");

    let mut a = GF::from(5);

    a.add_assign(a);
    println!("a to teraz 5");
    println!("a + a: {}", a.to_u64());

    a.sub_assign(a);
    println!("a - a: {}", a.to_u64());

    a.sub_assign(GF::from(1));
    println!("a - 1: {}", a.to_u64());

    a.div_assign(GF::from(2));
    println!("a / 2: {}", a.to_u64());

    a.mul_assign(GF::from(2));
    println!("a * 2: {}", a.to_u64());

}
}
