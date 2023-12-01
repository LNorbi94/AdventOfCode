use std::env;

mod day_1;
use day_1::day_1;

fn main() {
    let args : Vec<String> = env::args().collect();

    match args[1].as_str() {
        "1" => day_1(),
        &_ => todo!()
    }
}
