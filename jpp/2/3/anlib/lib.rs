pub fn factorial_rec(n: i32) -> i32{
    if n == 0 || n == 1 {
        return 1
    } else {
        return n * factorial_rec(n - 1);
    }
}

pub fn gcd_rec(mut a: i32, mut b: i32) -> i32 {
    if a < 0  {
        a = -a;
    }
    if b < 0 {
        b = -b;
    }

    if a == b {
        return a;
    } else if a > b {
        return gcd_rec(a - b, b)
    } else {
        return gcd_rec(a, b - a)
    }
}

pub struct SolutionRec {
    pub x: i32,
    pub y: i32,
    pub comment: String,
}

pub fn diof_rec(mut a: i32, mut b: i32, mut c: i32) -> SolutionRec {
    let mut result = SolutionRec {
        x: 0,
        y: 0,
        comment: String::new(),
    };
    let mut d: i32 = gcd_rec(a, b);

    if c % d != 0 {
        result.x = 0;
        result.y = 0;
        result.comment = String::from("Solution does not exist.");
        return result
    }

    let mut gcda: i32 = a / d;
    let mut gcdb: i32 = b / d;
    let mut gcdc: i32 = c / d;

    let mut x = 0;
    let mut y = 0;

    let gcd = gcd_extended_rec(gcda, gcdb, &mut x, &mut y);

    result.x = x * gcdc;
    result.y = y * gcdc;
    result.comment = String::from("Solution exists");

    return result
}

pub fn gcd_extended_rec(mut a: i32, mut b: i32, x: &mut i32, y: &mut i32) -> i32 {

    if a == 0 {
        *x = 0;
        *y = 1;
        return b;
    }

    let mut x1: i32 = 0;
    let mut y1: i32 = 0;
    let mut gcd = gcd_extended_rec(b % a, a, &mut x1, &mut y1);
    
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd
}