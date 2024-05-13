use num_traits::FromPrimitive;
//use num_bigint::RandBigInt;
//use num::BigUint;
//use rand::Rng;
use num_bigint::{BigUint, RandBigInt, BigInt, ToBigInt};
//use num_integer::Integer
use num::Integer;
use rand::thread_rng;
use num_traits::{One, Zero};

struct key_pair {
    n: BigUint,
    key: BigUint,
}

fn check_prime(n: &BigUint) -> bool {
    /*let root: BigUint = BigUint::sqrt(&n);

    for i in num_iter::range_inclusive(BigUint::from(2_u32), root) {
        if n.mod_floor(&i) == BigUint::from(0_u32) {
            return false;
        }
    }

    return true;*/  
    let mut i = BigUint::from(2_u32);
        while &i < &n.sqrt() {
           if n % &i == BigUint::from(0_u32) {
             return false;
           }
        i += 1_u32;
    }
    return true
}

fn is_coprime(a: &BigUint, b: &BigUint) -> bool {
    if b == &BigUint::from(0_u32) {
        return a == &BigUint::from(1_u32);
    }

    return is_coprime(b, &(a.mod_floor(b)));
}

fn find_e(euler: &BigUint) -> BigUint {
   /* //let mut rng = rand::thread_rng();
    println!("Im lookig for e...");
    let lo = BigUint::from(2_u32);
    let hi = euler - BigUint::from(2_u32);

    let mut e = generate_random(&lo, &hi);
    println!("Generated: {}", e);

    if !is_coprime(&e, euler) {
        let mut _e = e.clone();

        loop {
             if _e == (euler - BigUint::from(1_u32)) {
                _e = BigUint::from(2_u32)
             } else {
                 _e += BigUint::from(1_u32);
             }

            if !(_e != e) && is_coprime(&_e, euler) {
                break;
            }
        } 
        e = _e;
    }
    return e;*/
  /* let mut e = thread_rng().gen_biguint_range(&BigUint::from(0_u32), &(euler - 2u32)) + 2u32;
    let mut _e = e.clone();

    if !is_coprime(&e, euler) {
        loop {
            _e = if _e == (euler - 1u32) { BigUint::from(2u32) } else { &_e + 1u32 };
            if _e != e && !is_coprime(&_e, euler) && &_e % BigUint::from(2u32) != BigUint::from(0_u32) {

                break;
            }
        }
        e = _e;
    }
   return e*/ 

  let mut e = thread_rng().gen_biguint_range(&1_u32.into(), euler);
    let mut g = gcd(&e, euler);
    while g != 1_u32.into() {
        e = thread_rng().gen_biguint_range(&1_u32.into(), euler);
        g = gcd(&e, euler);
    }

    e
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
    let mut s0: BigInt = BigInt::from(1_u32);
    let mut s1: BigInt = BigInt::from(0_u32);
    let mut t0: BigInt = BigInt::from(0_u32);
    let mut t1: BigInt = BigInt::from(1_u32);
    let mut r0: BigInt = a.to_bigint().unwrap();
    let mut r1: BigInt = b.to_bigint().unwrap();

    while r1 != BigInt::from(0_u32) {
        let q: BigInt = &r0 / &r1;
        let mut temp: BigInt = r1.clone();
       // println!("Panik 1");
        r1 = &r0 - (&q * &r1);
        r0 = temp.clone();

        temp = s1.clone();
      //  println!("Panik 2");
        s1 = &s0 - &q * &s1; // o tutaj panikuje
        s0 = temp.clone();

        temp = t1.clone();
      //  println!("Panik 3");
        t1 = &t0 - (&q * &t1);
        t0 = temp.clone();
    }

   // println!("Wyjscie z petli");

    let mut ret: BigInt;
    if s0 < BigInt::from(0_u32) {
        let b_temp: BigInt = b.to_bigint().unwrap();
        ret = &s0 + b_temp;
    } else {
        ret = s0.clone();
    }

    return ret.to_biguint().unwrap();
}




fn calculate_keys(prime1: &BigUint, prime2: &BigUint) -> (key_pair, key_pair) {
    let calculated_n: BigUint = prime1 * prime2;
    println!("N was calculated...");
    let euler: BigUint = (prime1 - 1_u32) * (prime2 - 1_u32);
    println!("Euler was calculated: {}", euler);
    let e: BigUint = find_e(&euler);   // w tej funkcji jest problem na razie
    println!("E was calculated: {}", e);
    let d: BigUint = euclide(&e, &euler); //tutaj w sumie tez, biguint panikuje
    println!("D was calculated: {}", d);


    //println!("Euler: {}", euler);

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
    /*if a == &BigUint::from(0_u32) {
        return BigUint::from(0_u32);
    } 
    if b == &BigUint::from(0_u32) {
        return BigUint::from(1_u32);
    } 
    
    let mut y: BigUint;
    if b.mod_floor(&BigUint::from(2_u32)) == BigUint::from(0_u32) {
        y = power(a, &(b / &BigUint::from(2_u32)), n);
        y = (&y * &y).mod_floor(&n);
    } else {
        y = a * n;
        y = ((&y * power(a, &(b - &BigUint::from(1_u32)), n)).mod_floor(&n)).mod_floor(&n);
    }
    return ((y.mod_floor(&n)).mod_floor(&n));*/  

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


fn gcde(a: &BigUint, b: &BigUint) -> (BigUint, BigUint, BigUint) {
    let mut ret_x: BigUint;
    let mut ret_y: BigUint;
    let mut ret_b: BigUint;
    let mut ret: BigUint;

    if a == &BigUint::from(0_u32) {
        ret_x = BigUint::from(0_u32);
        ret_y = BigUint::from(1_u32);
        ret_b = b.clone();
        return (ret_b, ret_x, ret_y);
    }

    let mut x_temp: BigUint;
    let mut y_temp: BigUint;
    let mut gcd: BigUint;

    (gcd, x_temp, y_temp) = gcde(&(b.mod_floor(&a)), a);

    ret_x = &y_temp - (b / a) * &x_temp;
    ret_y = x_temp.clone();

    return (gcd, ret_x, ret_y);


/*let mut a = a.clone();
    let mut b = b.clone();
    let mut r;
    while b != BigUint::from(0_u32) {
        r = a % &b;
        a = b;
        b = r;
    }
    a*/

   
}




fn find_primes(priv_a: &key_pair, pub_a: &key_pair) -> (BigUint, BigUint) {
    let mut t: BigUint = &priv_a.key * &pub_a.key - &BigUint::from(1_u32);
    let mut n: BigUint = priv_a.n.clone();
    let mut kphi: BigUint = t.clone();

    while t.mod_floor(&BigUint::from(2_u32)) == BigUint::from(0_u32) {
        t = &t / BigUint::from(2_u32);
    }

    let mut a: BigUint = BigUint::from(2_u32);

    let mut k: BigUint;
    let mut x: BigUint;
    let mut r: BigUint;
    let mut q: BigUint;
    let mut p: BigUint = BigUint::from(1_u32);

    while (a < BigUint::from(100_u32)) {
        k = t.clone();
        while(k < kphi) {
            x = power(&a, &k, &n);

            if x != BigUint::from(1_u32) && x != (&n - BigUint::from(1_u32)) && power(&x, &BigUint::from(2_u32), &n) == BigUint::from(1_u32) {
                (p) = gcd(&(&x - BigUint::from(1_u32)), &n);
            }
            k = &k * BigUint::from(2_u32);
        }
        a = &a + BigUint::from(2_u32);
    }
    q = &n / &p;
    return (q, p);
  
}

fn crack(p: &BigUint, q: &BigUint, e: &BigUint) -> BigUint {
    let mut n: BigUint = p * q;
    let mut euler: BigUint = (p - 1_u32) * (q - 1_u32);
    let mut d = euclide(&e, &euler);
    return d;
} 


fn main() {
    let prime1: BigUint = "1234577".parse().unwrap();
    let prime2: BigUint = "1234567891".parse().unwrap();

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
    (pub_b, priv_b) = calculate_keys(&prime1, &prime2);

    println!("Your keys A: n, key");
    println!("Public: {}", pub_a.key);
    println!("Private: {}", priv_a.key);

    println!("Your keys B: n, key");
    println!("Public: {}", pub_b.key);
    println!("Private: {}", priv_b.key);

    println!("I have only pub_a, priv_a, pub_b. I'm looking for priv_b...");
    println!("Firstly, I'm looking for p and q.");
    let mut p: BigUint;
    let mut q: BigUint;
    (p, q) = find_primes(&priv_a, &pub_a);
    println!("Your keys: {}, {}", p, q);
    println!("Now, I'm calculating private key.");

    let mut calculated_priv: BigUint = crack(&p, &q, &pub_b.key);
    println!("Private key: {}", calculated_priv);

}
