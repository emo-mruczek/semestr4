use num_bigint::{BigUint, RandBigInt, BigInt, ToBigInt};
use num::Integer;
use rand::thread_rng;
use num_traits::{One, Zero};

struct key_pair {
    n: BigUint,
    key: BigUint,
}

fn check_prime(n: &BigUint) -> bool {
    let mut i = BigUint::from(2_u32);
        while &i < &n.sqrt() {
           if n % &i == BigUint::from(0_u32) {
             return false;
           }
        i += 1_u32;
    }
    return true;
}

fn find_e(euler: &BigUint) -> BigUint {
  let mut e = thread_rng().gen_biguint_range(&1_u32.into(), euler);
    let mut g = gcd(&e, euler);
    while g != 1_u32.into() {
        e = thread_rng().gen_biguint_range(&1_u32.into(), euler);
        g = gcd(&e, euler);
    }
   return  e;
}


fn gcd(a: &BigUint, b: &BigUint) -> BigUint {
    if b > a {
        return gcd(b, a);
    }
    let mut a = a.clone();
    let mut b = b.clone();
    let mut r;
    while b != BigUint::zero() {
        r = a % &b;
        a = b;
        b = r;
    }
    return a
}

fn euclide(a: &BigUint, b: &BigUint) -> BigUint {
    let mut s0: BigInt = BigInt::one();
    let mut s1: BigInt = BigInt::zero();
    let mut t0: BigInt = BigInt::zero();
    let mut t1: BigInt = BigInt::one();
    let mut r0: BigInt = a.to_bigint().unwrap();
    let mut r1: BigInt = b.to_bigint().unwrap();

    while r1 != BigInt::from(0_u32) {
        let q: BigInt = &r0 / &r1;
        let mut temp: BigInt = r1.clone();
        r1 = &r0 - (&q * &r1);
        r0 = temp.clone();

        temp = s1.clone();
        s1 = &s0 - &q * &s1;
        s0 = temp.clone();

        temp = t1.clone();
        t1 = &t0 - (&q * &t1);
        t0 = temp.clone();
    }

   // println!("Wyjscie z petli");

    let ret: BigInt;
    if s0 < BigInt::zero() {
        let b_temp: BigInt = b.to_bigint().unwrap();
        ret = &s0 + b_temp;
    } else {
        ret = s0.clone();
    }

    return ret.to_biguint().unwrap();
}

fn calculate_keys(prime1: &BigUint, prime2: &BigUint) -> (key_pair, key_pair) {
    let calculated_n: BigUint = prime1 * prime2;
    println!("N was calculated: {}", calculated_n);
    let euler: BigUint = (prime1 - 1_u32) * (prime2 - 1_u32);
    println!("Euler was calculated: {}", euler);
    let e: BigUint = find_e(&euler);
    println!("E was calculated: {}", e);
    let d: BigUint = euclide(&e, &euler); 
    println!("D was calculated: {}", d);

    let priv_key = key_pair {
        n: calculated_n.clone(),
        key: d.clone(),
    };

    let pub_key = key_pair {
        n: calculated_n.clone(),
        key: e.clone(),
    };

    return (priv_key, pub_key);
}

fn power(a: &BigUint, b: &BigUint, n: &BigUint) -> BigUint {
    let mut a = a.clone();
    let mut b = b.clone();
    let mut res = BigUint::one();
    while b > BigUint::zero() {
        if &b % 2u32 == 1u32.into() {
            res = (res * &a) % n;
        }
        a = (&a * &a) % n;
        b /= 2u32;
    }

    return res
}

fn find_primes(priv_a: &key_pair, pub_a: &key_pair) -> (BigUint, BigUint) {
    let mut t: BigUint = &priv_a.key * &pub_a.key - &BigUint::one();
    let n: BigUint = priv_a.n.clone();
    let kphi: BigUint = t.clone();

    while t.mod_floor(&BigUint::from(2_u32)) == BigUint::zero() {
        t = &t / BigUint::from(2_u32);
    }

    let mut a: BigUint = BigUint::from(2_u32);

    let mut k: BigUint;
    let mut x: BigUint;
    let q: BigUint;
    let mut p: BigUint = BigUint::one();

    while a < BigUint::from(100_u32) {
        k = t.clone();
        while k < kphi {
            x = power(&a, &k, &n);

            if x != BigUint::one() && x != (&n - BigUint::one()) && power(&x, &BigUint::from(2_u32), &n) == BigUint::one() {
                (p) = gcd(&(&x - BigUint::one()), &n);
            }
            k = &k * BigUint::from(2_u32);
        }
        a = &a + BigUint::from(2_u32);
    }
    q = &n / &p;
    return (q, p);
  
}

fn crack(p: &BigUint, q: &BigUint, e: &BigUint) -> BigUint {
    let euler: BigUint = (p - 1_u32) * (q - 1_u32);
    let d = euclide(&e, &euler);
    return d;
} 


fn main() {

    let arg1 = std::env::args().nth(1).expect("no prime1 given");
    let arg2 = std::env::args().nth(2).expect("no prime2 given");

    let prime1: BigUint = arg1.parse().unwrap();
    let prime2: BigUint = arg2.parse().unwrap();

   // let prime1: BigUint = "1234577".parse().unwrap();
   // let prime2: BigUint = "1234567891".parse().unwrap();

    let pub_a: key_pair;
    let priv_a: key_pair;
    let pub_b: key_pair;
    let priv_b: key_pair;

    if !check_prime(&prime1) || !check_prime(&prime2) || prime1 == prime2 {
        println!("Numbers are not prime or are not the same!!!");
        return;
    }

    println!("Numbers are ok :)");

    (pub_a, priv_a) = calculate_keys(&prime1, &prime2);
    (pub_b, priv_b) = calculate_keys(&prime1, &prime2);

    println!("Your keys A: n, key");
    println!("Public: {}", pub_a.key);
    println!("Private: {}", priv_a.key);

    println!("Your keys B: n, key");
    println!("Public: {}", pub_b.key);
    println!("Private: {}", priv_b.key);

    println!("I have only pub_a, priv_a, pub_b. I'm looking for priv_b...");
    println!("Firstly, I'm looking for p and q.");
    let p: BigUint;
    let q: BigUint;
    (p, q) = find_primes(&priv_a, &pub_a);
    println!("Your primes: {}, {}", p, q);
    println!("Now, I'm calculating private key.");

    let calculated_priv: BigUint = crack(&p, &q, &pub_b.key);
    println!("Private key: {}", calculated_priv);

    if calculated_priv == priv_b.key {
        println!("Cracked!");
    } else {
        println!("It's not correct!");
    }
}
