use num_bigint::BigUint;
use num_traits::FromPrimitive;

struct key_pair {
    n: BigUint,
    key: BigUint,
}


fn main() {
    let mut prime1: BigUint = "37".parse().unwrap();
    let mut prime2: BigUint = "53".parse().unwrap();

    let mut pub_a: key_pair;
    let mut priv_a: key_pair;
    let mut pub_b: key_pair;
    let mut priv_b: key_pair;

    if (!check_prime(primea) || !check_prime(primeb) || primea == primeb) {
        println!("Numbers are not prime or are not the same!!!");
        return;
    }

    calculate_keys()



    println!("Your keys A: n, key");
    println!("Public: {}", prime1);
    println!("Private: {}", prime2);
}
