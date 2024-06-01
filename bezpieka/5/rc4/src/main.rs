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
fn prga(S: &mut [u8; LENGTH], input: &[u8]) -> Vec<u8> {
    let mut output = vec![0u8; input.len()];
    let mut i = 0;
    let mut j = 0;

    for (n, &byte) in input.iter().enumerate() {
        i = (i + 1) % LENGTH;
        j = (S[i] as usize + j) % LENGTH;
        S.swap(i, j);
        
        let index = (S[i] as usize + S[j] as usize) % LENGTH;
        let k = S[index];
        output[n] = k ^ byte; // XOR
    }

    output
}

fn encode_rc4(input: &[u8], key: &[u8]) -> Vec<u8> {
    let mut S = [0u8; LENGTH];
    ksa(&mut S, key);
    prga(&mut S, input)
}

// jest symetryczny
fn decode_rc4(input: &[u8], key: &[u8]) -> Vec<u8> {
    encode_rc4(input, key) 
}


// NRB - unikatowy, 26 cyfr
// 2 - liczba kontrolna
// 8 - numer rozliczeniowy
// 16 - numer porzadkowy
// nr rozliczeniowe: https://bankoweabc.pl/numery-rozliczeniowe-bankow-w-polsce/
// wyliczanie liczby kontrolnej: https://bankoweabc.pl/2021/05/05/cyfry-w-numerze-rachunku-bankowego/
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

    let mut num_str = String::with_capacity(28);
    for &digit in &num {
        num_str.push(char::from_digit(digit as u32, 10).unwrap());
    }

    let num_pl = 2521;
    let ctrl_num_str = format!("{}{}", &num_str[2..26], &num_pl );

    let num_ctrl: u128 = ctrl_num_str.parse().unwrap();
    let control_number = 98 - (num_ctrl % 97);

    res.push_str(&format!("{:02}", control_number));
    res.push_str(&num_str[2..]);

    println!("{}", res);
    res
}

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
    let input1 = b"testjeden";
    let input2 = b"testdwa";
    let key = b"taki";

    let output1 = encode_rc4(input1, key);
    let output2 = encode_rc4(input2, key);

    let ok = is_same_key(&output1, &output2);

    if ok {
        println!("Git");
    } else {
        println!("Niegit");
    }
}


// known plaintext attack
// znam plaintext oraz to, jak wyglada po zakodowaniu (plaintext, encoded)
// result jest zakodowany tym samym kodem, co encoded
// z wlasnosci xor-a moge wyznaczyc wyglad bajtu przed zakodowaniem
// a xor b xor b = a
fn find_bank_number(plaintext: &[u8], encoded: &[u8], result: &[u8]) -> Option<String> {
    let mut decoded = Vec::with_capacity(result.len());

    for i in 0..result.len() {
        let a = plaintext[i % plaintext.len()];
        let b = encoded[i % encoded.len()];
        let c = result[i];
        let d = (a ^ b) ^ c;

        if !d.is_ascii_digit() {
            return None;
        } else {
            decoded.push(d);
        }
    }

    Some(String::from_utf8(decoded).unwrap())
}

fn main() {


    let args: Vec<String> = env::args().collect();

    if args.len() < 3 {
        eprintln!("Enter inputs.");
        return;
    }

    let key = args[1].as_bytes();
    let input = args[2].as_bytes();

    println!("{}", String::from_utf8_lossy(input));

    let output = encode_rc4(input, key);

    for byte in &output {
        print!("{:02X} ", byte);
    }
    println!();

    let encoded = decode_rc4(&output, key);

    println!("{}", String::from_utf8_lossy(&encoded));

    test_key();


    // banki
    let bank_numbers: [[u8; 8]; 5] = [
        [1, 0, 1, 0, 0, 0, 0, 0], // NBP
        [1, 0, 2, 0, 1, 0, 9, 7], // PKO BP, oddział 8 w WWA
        [1, 0, 5, 0, 1, 9, 2, 4], // ING, oddział Pruszków ul Ołówkowa 1d
        [1, 2, 4, 0, 5, 4, 8, 4], // Pekao, oddział w Gdańsku ul Franciszka Rakoczego 17
        [1, 7, 5, 0, 1, 2, 8, 1], // BNP Paribas, oddział w Poznaniu al. Solidarności 36
    ];

    let mut generated_bank_numbers_encrypted: Vec<Vec<u8>> = Vec::new();
    let mut generated_bank_numbers_plaintext: Vec<String> = Vec::new();

    let key = b"2137";

    for i in 0..5 {
        for _ in 0..5 {
            let result = generate_nbr(&bank_numbers[i]);
            generated_bank_numbers_plaintext.push(result.clone());
            let result_bytes = result.as_bytes();

            let encrypted = encode_rc4(result_bytes, key);
            generated_bank_numbers_encrypted.push(encrypted);
        }
    }

    let result = generate_nbr(&bank_numbers[1]);
    let encrypted = encode_rc4(result.as_bytes(), key);

    let decrypted = find_bank_number(result.as_bytes(), &encrypted, &generated_bank_numbers_encrypted[1]);
    println!("Szukano: {}", generated_bank_numbers_plaintext[1]);
    println!("Znaleziono: {}", decrypted.unwrap_or_else(|| String::from("nie udalo sie")));
}
