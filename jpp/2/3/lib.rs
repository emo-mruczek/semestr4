pub fn factorial_loop(n: i32) -> i32{
    let mut result: i32 = 1;

    for i in 1..n+1 {
        result *= i;
    }

    return result
}

pub fn gcd_loop(mut a: i32, mut b: i32) -> i32 {
    if a < 0  {
        a = -a;
    }
    if b < 0 {
        b = -b;
    }

    while a!=b
    {
        if a > b {
            a -= b;
        }
        else {
            b -= a;
        }
    }
    return a;
}

pub struct SolutionLoop {
    pub x: i32,
    pub y: i32,
    pub comment: String,
}

pub fn diof_loop(mut a: i32, mut b: i32, mut c: i32) -> SolutionLoop {
    let mut result = SolutionLoop {
        x: 0,
        y: 0,
        comment: String::new(),
    };
    let mut d: i32 = gcd_loop(a, b);

    if c % d != 0 {
        result.x = 0;
        result.y = 0;
        result.comment = String::from("Solution does not exist.");
        return result
    }

    let mut gcda: i32 = a / d;
    let mut gcdb: i32 = b / d;
    let mut gcdc: i32 = c / d;

    let (gcd, x, y) = gcd_extended_loop(gcda, gcdb);

    result.x = x * gcdc;
    result.y = y * gcdc;
    result.comment = String::from("Solution exist");

    return result

}

pub fn gcd_extended_loop(mut a: i32, mut b: i32) -> (i32, i32, i32) {
    let mut x1: i32 = 0;
    let mut y1: i32 = 1;
    let mut x_curr: i32 = 1;
    let mut y_curr: i32 = 0;

    while a != 0 {
        let mut quotient: i32 = b / a;

        let mut temp_x: i32 = x_curr - quotient * x1;
        let mut temp_y: i32 = y_curr - quotient * y1;
 
        x_curr = x1;
        y_curr = y1;
        x1 = temp_x;
        y1 = temp_y;
 
        let mut temp: i32 = a;
        a = b % a;
        b = temp;
    }

    return (b, x_curr, y_curr)

}