use std::path::Path;

fn parse_input(file_path : &Path) -> Vec<i32> {
    let mut vec = Vec::new();
    let contents = std::fs::read_to_string(file_path).expect("Could not find file with such name.");
    let contents = contents.split("\n");
    let mut actual_calorie_count = 0;
    for line in contents {
        match line.trim().parse::<i32>() {
            Ok(n) => actual_calorie_count += n,
            Err(_e) => { vec.push(actual_calorie_count); actual_calorie_count = 0; }
        }
    }
    if actual_calorie_count > 0 {
        vec.push(actual_calorie_count);
    }
    vec
}

fn get_first_nth_calories_sum(calorie_counts : &Vec<i32>, n : usize) {
    let highest_calorie_count : i32 = calorie_counts.iter().rev().take(n).sum();
    println!("First {n} calorie count summed was: {highest_calorie_count}");
}

pub fn day_1(task : i32, input_file : i32) {
    let file_path : &Path;
    if input_file == 1 {
        file_path = Path::new(r"..\input_files\day_1_a.txt")
    } else if input_file == 2 {
        file_path = Path::new(r"..\input_files\day_1_b.txt")
    } else {
        panic!("Invalid input file was given.")
    }

    let mut calorie_counts = parse_input(file_path);
    calorie_counts.sort();
    if task == 1 {
        get_first_nth_calories_sum(&calorie_counts, 1);
    } else if task == 2 {
        get_first_nth_calories_sum(&calorie_counts, 3);
    }
}
