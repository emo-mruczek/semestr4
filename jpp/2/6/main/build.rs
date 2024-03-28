extern crate cc;

fn main() {
    cc::Build::new()
        .file("src/libloop.c")
        .shared_flag(true)
        .compile("libloop.a");
        

    cc::Build::new()
        .file("src/librec.c")
        .shared_flag(true)
        .compile("librec.a");
}
