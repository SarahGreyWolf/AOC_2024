use std::fs::File;
use std::io::{self, Read};

fn main() -> io::Result<()> {
    let mut args = std::env::args().skip(1);
    if args.len() < 1 {
        eprintln!("Usage: day_1 <path_to_input>");
        return Ok(());
    }

    let path = args.next().unwrap();

    // Read List
    let mut file = File::open(path)?;
    let mut buffer = String::new();
    let _ = file.read_to_string(&mut buffer);
    // Split Each Line By Space
    let lines = buffer.lines();
    // Build a list for left and right list
    let (mut left, mut right): (Vec<u64>, Vec<u64>) = lines
        .map(|line| {
            let split = line.split("   ").collect::<Vec<&str>>();
            (
                split[0].parse::<u64>().unwrap(),
                split[1].parse::<u64>().unwrap(),
            )
        })
        .collect();
    // Sort left & right list smallest to highest
    left.sort();
    right.sort();

    part_1(&left, &right);
    part_2(&left, &right);

    Ok(())
}

fn part_1(left: &[u64], right: &[u64]) {
    // Iterate through lists
    //      Find difference of the two numbers
    //      Add to new list
    assert_eq!(left.len(), right.len());
    let diffs: Vec<u64> = left
        .iter()
        .zip(right)
        .map(|(l, r)| l.abs_diff(*r))
        .collect();
    // Sum the diffs
    let sum: u64 = diffs.iter().sum();
    println!("The SUM of the differences in location ID's is {}", sum);
}

fn part_2(left: &[u64], right: &[u64]) {
    // Iterate over the lists
    // Count how often the item appears in right list
    // Multiply the Item by the count
    // Store to a new list
    assert_eq!(left.len(), right.len());
    let matches: Vec<usize> = left
        .iter()
        .map(|l| *l as usize * right.iter().filter(|r| *r == l).count())
        .collect();
    // Sum the scores
    let sum: usize = matches.iter().sum();
    println!("The SUM of the matches in location ID's is {}", sum);
}
