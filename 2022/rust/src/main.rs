use std::env;

mod day_1;
use day_1::day_1;

fn main() {
    let args : Vec<String> = env::args().collect();

    let mut task : i32 = 1;
    let mut input_file : i32 = 2;

    if args.len() > 2 {
        match args[2].as_str() {
            "1" => task = 1,
            "2" => task = 2,
            &_ => todo!()
        }
    }

    if args.len() > 3 {
        match args[3].as_str() {
            "1" => input_file = 1,
            "2" => input_file = 2,
            &_ => todo!()
        }
    }

    match args[1].as_str() {
        "1" => day_1(task, input_file),
        &_ => todo!()
    }
}
