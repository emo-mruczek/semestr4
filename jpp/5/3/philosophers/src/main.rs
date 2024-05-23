use std::{thread, time::Duration, sync::{Arc, Mutex} };
use rand::Rng;

const NUM_PHILOSOPHERS: u16 = 5;
const NUM_PHILOSOPHERS_USIZE: usize = 5;
const NUM_MEALS: u16 = 3;

const MIN_TIME: u16 = 400;
const MAX_TIME: u16 = 1000;

#[derive(Clone, Copy, PartialEq)]
enum State {
    THINKING,
    HUNGRY,
    EATING,
}

fn random_time() -> u16 {
    let num = rand::thread_rng().gen_range(MIN_TIME..MAX_TIME);
    return num
}

fn think(n: u16, print_mu: Arc<Mutex<()>>) {
    {
        let _lock = print_mu.lock().unwrap();
        println!("The {} philosopher is thinking", n);
    }
    let num = random_time();
    thread::sleep(Duration::from_millis(u64::from(num)));
}

fn test(n: u16, status: &mut [State; NUM_PHILOSOPHERS_USIZE]) {
    let left: u16 = (n - 1 + NUM_PHILOSOPHERS) % NUM_PHILOSOPHERS;
    let right: u16 = (n + 1) % NUM_PHILOSOPHERS;
    if status[usize::from(n)] == State::HUNGRY && status[usize::from(left)] != State::EATING && status[usize::from(right)] != State::EATING {
        status[usize::from(n)] = State::EATING;
        //forks semaphore
    }
}

fn take_forks(n: u16, print_mu: Arc<Mutex<()>>, forks_mu: Arc<Mutex<()>>, status: &mut [State; NUM_PHILOSOPHERS_USIZE]) {
    let _lockfork = forks_mu.lock().unwrap();
    status[usize::from(n)] = State::HUNGRY;
    {
        let _lockprint = print_mu.lock().unwrap();
        println!("The {} philosopher is hungry", n);
    }
    test(n, status);
    //forksemaphores
}

fn eat(n: u16, print_mu: Arc<Mutex<()>>) {
    {
        let _lock = print_mu.lock().unwrap();
        println!("The {} philosopher is eating", n);
    }
    let num = random_time();
    thread::sleep(Duration::from_millis(u64::from(num)));
}

fn put_forks(n: u16, forks_mu: Arc<Mutex<()>>, status: &mut [State; NUM_PHILOSOPHERS_USIZE]) {
    let left: u16 = (n - 1 + NUM_PHILOSOPHERS) % NUM_PHILOSOPHERS;
    let right: u16 = (n + 1) % NUM_PHILOSOPHERS;
    let _lockfork = forks_mu.lock().unwrap();
    status[usize::from(n)] = State::THINKING;
    test(left, status);
    test(right, status);
}

fn test_all(status: &mut [State; NUM_PHILOSOPHERS_USIZE]) {
    for i in NUM_PHILOSOPHERS_USIZE {
        test(i, &mut *status.lock().unwrap());
    }
}


fn philosopher(n: u16, print_mu: Arc<Mutex<()>>, forks_mu: Arc<Mutex<()>>, status: Arc<Mutex<[State; NUM_PHILOSOPHERS_USIZE]>>) {
    let mut meals_eaten = 0;
    loop {
        think(n, Arc::clone(&print_mu));
        take_forks(n, Arc::clone(&print_mu), Arc::clone(&forks_mu), &mut *status.lock().unwrap());
        eat(n, Arc::clone(&print_mu));
        put_forks(n, Arc::clone(&forks_mu), &mut *status.lock().unwrap());


        meals_eaten += 1;
        if meals_eaten == NUM_MEALS {
            // mutex sie zwalnia gdy wyjdzie za scope
            { let _lock = print_mu.lock().unwrap();
            println!("Finished eating! {}", n);
            }
            test_all(&mut *status.lock().unwrap());

            return
        }
    }
}

fn main() {
    // https://doc.rust-lang.org/rust-by-example/std_misc/threads.html
    let mut philosophers = vec![];
    let print_mu = Arc::new(Mutex::new(()));
    let forks_mu = Arc::new(Mutex::new(()));
    let status = Arc::new(Mutex::new([State::THINKING; NUM_PHILOSOPHERS_USIZE]));

    for i in 0..NUM_PHILOSOPHERS {
        let print_mu_clone = Arc::clone(&print_mu);
        let forks_mu_clone = Arc::clone(&forks_mu);
        let status_clone = Arc::clone(&status);
        philosophers.push(thread::spawn(move || {
            philosopher(i, print_mu_clone, forks_mu_clone, status_clone);
        }));
    }

    for handle in philosophers {
        handle.join().unwrap();
    }
}
