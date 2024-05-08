use num_traits::FromPrimitive;
//use num_bigint::RandBigInt;
//use num::BigUint;
//use rand::Rng;
use num_bigint::{BigUint, RandBigInt};

struct key_pair {
    n: BigUint,
    key: BigUint,
}

fn check_prime(n: &BigUint) -> bool {
    let root: BigUint = BigUint::sqrt(&n);

    for i in num_iter::range_inclusive(BigUint::from(2_u32), root) {
        if n % i == BigUint::from(0_u32) {
            return false;
        }
    }

    return true;
}

fn is_coprime(a: &BigUint, b: &BigUint) -> bool {
    if b == &BigUint::from(0_u32) {
        return a == &BigUint::from(1_u32);
    }

    return is_coprime(&b, &(a % b));
}

fn generate_random(lo: &BigUint, hi: &BigUint) -> BigUint {
   println!("Im generating a random number..."); 
  let mut rng = rand::thread_rng();
  let mut random_biguint = rng.gen_biguint_range(lo, hi);
  return random_biguint;
}

fn find_e(euler: &BigUint) -> BigUint {
    //let mut rng = rand::thread_rng();
    println!("Im lookig for e...");
    let lo = BigUint::from(2_u32);
    let hi = euler - BigUint::from(2_u32);

    let mut e = generate_random(&lo, &hi);

    if !is_coprime(&e, euler) {
        let mut _e = e.clone();

        loop {

             if _e == (euler - BigUint::from(1_u32)) {
                _e = BigUint::from(2_u32)
             } else {
                 _e = &_e + BigUint::from(1_u32);
             }

            if !(_e != e) && is_coprime(&_e, euler) {
                break;
            }
        } 

        e = _e;
    }

    return e;
}


fn calculate_keys(prime1: &BigUint, prime2: &BigUint) -> (key_pair, key_pair) {
    let calculated_n: BigUint = prime1 * prime2;
    println!("N was calculated...");
    let euler: BigUint = (prime1 - 1_u32) * (prime2 - 1_u32);
    println!("Euler was calculated...");
    let e: BigUint = find_e(&euler);   // w tej funkcji jest problem na razie
    println!("E was calculated...");


    //println!("Euler: {}", euler);

    let priv_key = key_pair {
        n: calculated_n.clone(),
        key: euler.clone(),
    };

    let pub_key = key_pair {
        n: calculated_n.clone(),
        key: e.clone(),
    };

    return (priv_key, pub_key);

}


fn main() {
    let prime1: BigUint = "37".parse().unwrap();
    let prime2: BigUint = "53".parse().unwrap();

    let mut pub_a: key_pair;
    let mut priv_a: key_pair;
    let mut pub_b: key_pair;
    let mut priv_b: key_pair;

    if !check_prime(&prime1) || !check_prime(&prime2) || prime1 == prime2 {
        println!("Numbers are not prime or are not the same!!!");
        return;
    }

    println!("Numbers are ok :)");

    (pub_a, priv_a) = calculate_keys(&prime1, &prime2);



    println!("Your keys A: n, key");
    println!("Public: {}", pub_a.key);
    println!("Private: {}", prime2);
}
