extern crate libc;

#[repr(C)]
pub struct solutionLoop {
  pub x: libc::c_int,
  pub y: libc::c_int,
  pub comment: libc::c_int
}

#[repr(C)]
pub struct solutionRec {
  pub x: libc::c_int,
  pub y: libc::c_int,
  pub comment: libc::c_int
}

extern "C" {
 //  pub fn factorialLoop(
  //     a: libc::c_int,
  // ) -> libc::c_int;
   
   pub fn gcdLoop(
        a: libc::c_int,
        b: libc::c_int
    ) -> libc::c_int;

    pub fn factorialLoopp(n: libc::c_int) -> libc::c_int;

    pub fn diofLoop(
      a: libc::c_int,
        b: libc::c_int,
        c: libc::c_int
   ) -> solutionLoop;

   pub fn factorialRec(n: libc::c_int) -> libc::c_int;

   pub fn gcdRec(
    a: libc::c_int,
    b: libc::c_int
) -> libc::c_int;


pub fn diofRec(
  a: libc::c_int,
    b: libc::c_int,
    c: libc::c_int
) -> solutionRec;
  
}

fn main() {
  unsafe {
  let mut fac: i32 = factorialLoopp(5);
    let mut gcd: i32 = gcdLoop(10, 5);
    let diofL: solutionLoop = diofLoop(1027, 712, 1);

    println!("For loop implementation:\n a) {}\n b) {}\n c) {} and {} ({})\n", fac, gcd, diofL.x, diofL.y, diofL.comment);

    fac = factorialRec(5);
    gcd = gcdRec(10, 5);
    let diofR: solutionRec = diofRec(1027, 712, 1);

    println!("For recursive implementation:\n a) {}\n b) {}\n c) {} and {} ({})\n", fac, gcd, diofR.x, diofR.y, diofR.comment);
}
}