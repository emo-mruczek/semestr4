use libloop::factorial_loop;
use libloop::gcd_loop;
use libloop::diof_loop;
use librec::factorial_rec;
use librec::gcd_rec;
use librec::diof_rec;


fn main() {
    let mut fac: i32 = factorial_loop(5);
    let mut gcd: i32 = gcd_loop(10, 5);
    let diofL = diof_loop(1027, 712, 1);

    println!("For loop implementation:\n a) {}\n b) {}\n c) {} and {} ({})\n", fac, gcd, diofL.x, diofL.y, diofL.comment);

    fac = factorial_rec(5);
    gcd = gcd_rec(10, 5);
    let diofR = diof_rec(1027, 712, 1);

    println!("For recursive implementation:\n a) {}\n b) {}\n c) {} and {} ({})\n", fac, gcd, diofR.x, diofR.y, diofR.comment);
}
