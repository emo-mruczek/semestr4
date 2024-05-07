use rand::{thread_rng, Rng};

#[derive(Clone, Copy, Debug, PartialEq)]
struct Key {
    n: u64,
    key: u64,
}

#[derive(Clone, Copy, Debug, PartialEq)]
struct KeyPair {
    private: Key,
    public: Key,
}

fn is_prime(n: u64) -> bool {
    for i in 2..((n as f32).sqrt() as u64) {
        if n % i == 0 {
            return false;
        }
    }
    true
}

fn euclid(a: u64, b: u64) -> u64 {
    let mut s0 = 1i64;
    let mut s1 = 0i64;
    let mut t0 = 0i64;
    let mut t1 = 1i64;
    let mut r0 = a as i64;
    let mut r1 = b as i64;

    while r1 != 0 {
        let q = r0 / r1;
        let mut temp = r1;
        r1 = r0 - q * r1;
        r0 = temp;

        temp = s1;
        s1 = s0 - q * s1;
        s0 = temp;

        temp = t1;
        t1 = t0 - q * t1;
        t0 = temp;
    }

    if s0 < 0 { (s0 + b as i64) as u64 } else { s0 as u64 }
}

fn find_e(p1: u64, p2: u64, phi: u64) -> u64 {
    let mut e = (2 + thread_rng().gen::<u64>()) % phi;
    while phi % e == 0 {
        e = (2 + thread_rng().gen::<u64>()) % phi;
        if is_prime(e) && e != p1 && e != p2 {
            return e;
        }
    }

    e
}

fn generate_key_pair(p1: u64, p2: u64) -> Option<KeyPair> {
    if !is_prime(p1) || !is_prime(p2) || p1 == p2 {
        return None;
    }

    let n = p1 as u64 * p2 as u64;
    let phi = (p1 - 1) * (p2 - 1);

    let e: u64 = find_e(p1, p2, phi);

    let d = euclid(e, phi);

    Some(
        KeyPair {
            private: Key { n, key: d },
            public: Key { n, key: e }
        }
    )
}

fn gcd(mut a: u64, mut b: u64) -> u64 {
    let mut r;
    while b != 0 {
        r = a % b;
        a = b;
        b = r;
    }
    a
}

// fn extended_gcd(a: u64, b: u64, x: &mut u64, y: &mut u64) -> u64 {
//     if a == 0 {
//         *x = 0;
//         *y = 1;
//         return b;
//     }
//
//     let mut x1 = 064;
//     let mut y1 = 0u64;
//     let gcd = extended_gcd(a, b, &mut x1, &mut y1);
//
//     *x = y1 - (b / a) * x1;
//     *y = x1;
//
//     gcd
// }

/// (a^exp) % n
fn pow_mod(mut a: u64, mut exp: u64, n: u64) -> u64 {
    let mut res = 1;

    while exp > 0 {
        if exp % 2 == 1 {
            res = (res * a) % n;
        }

        exp /= 2;

        a *= a;
    }

    res
}

fn find_private_key(pair_a: KeyPair, public_b: Key) -> Key {
    let kphi = pair_a.private.key * pair_a.public.key - 1;
    let n = public_b.n;
    let mut t = kphi;
    while t % 2 == 0 {
        t /= 2;
    }
    
    let mut p = 1;

    let mut a = 2u64;
    while a < 100 {
        let mut k = t;
        while k < kphi {
            let x = pow_mod(a, k, n);
            if x != t && x != (n - 1) && pow_mod(x, 2, n) == 1 {
                p = gcd(x - 1, n);
                break;
            }
            k *= 2;
        }
        a += 2;
    }

    let q = n / p;
    dbg!(q);

    Key { n: p, key: q }
}

fn main() {
    let p1 = 37;
    let p2 = 53;

    let pair_a = generate_key_pair(p1, p2)
        .expect("failed to generate key pair a");

    let pair_b = generate_key_pair(p1, p2)
        .expect("failed to generate key pair b");

    println!("private key A: {:?}", pair_a.private);
    println!("public key A: {:?}", pair_a.public);
    println!("private key B: {:?}", pair_b.private);
    println!("public key B: {:?}", pair_b.public);

    let found_b = find_private_key(pair_a, pair_b.public);
    println!("found_b: {:?}", found_b);
    if found_b == pair_b.private {
        println!("cracked B)");
    } else {
        println!("uncracked B(");
    }
}
