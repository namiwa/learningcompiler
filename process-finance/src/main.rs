use std::{error::Error, io, process};

fn example() -> Result<(), Box<dyn Error>> {
    let mut rdr = csv::ReaderBuilder::new()
        .has_headers(false)
        .from_reader(io::stdin());
    // skip 4 lines?
    let mut iter = rdr.records();

    while let Some(val) = iter.next() {
        match val {
            Ok(rec) => {
                println!("{}", rec.as_slice())
            }
            Err(err) => {
                print!("{}", err)
            }
        }
    }
    Ok(())
}

fn main() {
    if let Err(err) = example() {
        println!("error running example: {}", err);
        process::exit(1);
    }
}
