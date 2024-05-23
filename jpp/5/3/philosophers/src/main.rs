use std::{thread, sync::Arc };

const NUM_PHILOSOPHERS: u32 = 5;
const NUM_MEALS: u32 = 3;

fn philosopher(n: u32) {
    let mut meals_eaten = 0;
    loop {
        meals_eaten += 1;
        println!("dupa {}", n);
        if meals_eaten == NUM_MEALS {
            println!("Finished eating! {}", n);
            return
        }
    }
}

fn main() {
    // https://doc.rust-lang.org/rust-by-example/std_misc/threads.html
    let mut philosophers = vec![];

    for i in 0..NUM_PHILOSOPHERS {
        philosophers.push(thread::spawn(move || {
            philosopher(i);
        }));
    }

    for handle in philosophers {
        handle.join().unwrap();
    }
}
