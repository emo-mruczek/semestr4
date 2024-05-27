use std::env;
use rand::Rng;

const LENGTH: usize = 256;

// key-scheduling algorithm do inicjalizacji permutacji tablicy S
fn ksa(S: &mut [u8; LENGTH], key: &[u8]) {
    let keylength = key.len();

    for i in 0..LENGTH {
        S[i] = i as u8;
    }

    let mut j = 0;
    for i in 0..LENGTH {
        j = (j + S[i] as usize + key[i % keylength] as usize) % LENGTH;
        S.swap(i, j);
    }
}

// pseudo-random generation algorithm
fn rpga(S: &mut [u8; LENGTH], input: &[u8], output: &mut [u8]) {
    let mut i = 0;
    let mut j = 0;
    let len = input.len();

    for n in 0..len {
        i = (i + 1) % LENGTH;
        j = (S[i] as usize + j) % LENGTH;
        S.swap(i, j);
        
        let index = (S[i] as usize + S[j] as usize) % LENGTH;
        let k = S[index];
        output[n] = k ^ input[n]; // XOR
    }
}

fn encode_rc4(input: &[u8], output: &mut [u8], key: &[u8]) {
    let mut S = [0u8; LENGTH];

    ksa(&mut S, key);
    rpga(&mut S, input, output);
}

fn decode_rc4(input: &[u8], output: &mut [u8], key: &[u8]) {
    let mut S = [0u8; LENGTH];

    ksa(&mut S, key);
    rpga(&mut S, input, output);
}

// 0x80 -> most significant bit
fn is_same_key(input1: &[u8], input2: &[u8]) -> bool {
    let len1 = input1.len();
    let len2 = input2.len();
    let len = len1.min(len2);

    for i in 0..len {
        let test = input1[i] ^ input2[i];
        println!("{:02X}", test);
        if test >= 0x80 {
            return false;
        }
    }
    true
}

fn test_key() {
    let input1 = b"hahapapiez";
    let input2 = b"twojastara";
    let key = b"taki";
    let key2 = b"taki";

    let mut output1 = vec![0u8; input1.len()];
    let mut output2 = vec![0u8; input2.len()];

    encode_rc4(input1, &mut output1, key);
    encode_rc4(input2, &mut output2, key2);

    let ok = is_same_key(&output1, &output2);

    if ok {
        println!("Git");
    } else {
        println!("Niegit");
    }
}

// NRB - unikatowy, 26 cyfr
// 2 - liczba kontrolna
// 8 - numer rozliczeniowy
// 16 - numer porzadkowy
// nr rozliczeniowe: https://bankoweabc.pl/numery-rozliczeniowe-bankow-w-polsce/
// wyliczanie liczby kontrolnej: https://bankoweabc.pl/2021/05/05/cyfry-w-numerze-rachunku-bankowego/
//
// https://pl.wikipedia.org/wiki/Numeracja_rachunku_bankowego
fn generate_nbr(bank_num: &[u8]) -> String {

    let mut res = String::new();

    let mut num = [0u8; 26];
    for i in 10..26 {
        num[i] = rand::thread_rng().gen_range(0..10);
    }

    let mut j = 0;
    for i in 2..10 {
        num[i] = bank_num[j];
        j += 1;
    }

    let num_pl = 2521;

    let mut ctrl: u128 = 0;

    for i in 0..26 {
        ctrl += num[i] as u128 * 10u128.pow((29 - i) as u32); 
    }

    let ctrl: u128 = ctrl + num_pl;

    let reminder: u128 = ctrl % 97;
    let final_ctr = 98 - reminder;
    
    res.push_str(format!("{:02}", final_ctr).as_str());

    let ctrl_str = ctrl.to_string();
    let final_ctrl_str = &ctrl_str[..ctrl_str.len() - 4];  
    res.push_str(&final_ctrl_str);


    println!("{}", ctrl_str);

    return res;

} 

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 3 {
        eprintln!("Enter inputs.");
        return;
    }

    let key = args[1].as_bytes();
    let input = args[2].as_bytes();

    let mut output = vec![0u8; input.len()];

    println!("{}", String::from_utf8_lossy(input));

    encode_rc4(input, &mut output, key);

    for byte in &output {
        print!("{:02X} ", byte);
    }
    println!();

    let mut encoded = vec![0u8; input.len()];

    decode_rc4(&output, &mut encoded, key);

    println!("{}", String::from_utf8_lossy(&encoded));

    let bank_numbers: [[u8; 8]; 5] = [
        [1, 0, 1, 0, 0, 0, 0, 0], // NBP
        [1, 0, 2, 0, 1, 0, 9, 7], // PKO BP, oddział 8 w WWA
        [1, 0, 5, 0, 1, 9, 2, 4], // ING, oddział pruszków ul Ołówkowa 1d
        [1, 2, 4, 0, 5, 4, 8, 4], // Pekao, oddział w Gdańsku ul Franciszka Rakoczego 17
        [1, 7, 5, 0, 1, 2, 8, 1], // BNP Paribas, oddział w Poznaniu al. Solidarności 36
    ];

    //test_key();
    
    let result = generate_nbr(&bank_numbers[0]);
    println!("{:?}", result);

    // Freeing memory is handled automatically in Rust
}
