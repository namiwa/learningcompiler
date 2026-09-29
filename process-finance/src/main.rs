use clap::Parser;
use std::{error::Error, io, path::PathBuf, process};

#[derive(Parser)]
struct Cli {
    // target file path
    path: std::path::PathBuf,
}

fn test_csv(fp: std::path::PathBuf) -> Result<(), Box<dyn Error>> {
    let mut rdr = csv::ReaderBuilder::new()
        .has_headers(false)
        .delimiter(b'\t')
        .from_path(fp);

    // skip 4 lines?
    let mut iter = rdr.as_mut().unwrap().records();

    while let Some(val) = iter.next() {
        match val {
            Ok(rec) => {
                println!("{}", rec.as_slice())
            }
            Err(err) => {}
        }
    }
    Ok(())
}

fn process_file(fp: PathBuf) -> Result<String, std::io::Error> {
    let content = std::fs::read_to_string(fp);
    println!("in process file");
    match content {
        Err(content) => {
            println!("file read error {}", content);
            Err(content)
        }
        Ok(content) => {
            let mut store: Vec<&str> = vec![];
            for line in content.lines() {
                if line.is_empty() {
                    continue;
                } else {
                    let val = line.trim();
                    println!("{}", val);
                    store.push(val);
                }
            }

            println!("finish file process");
            let test = String::from_iter(store);

            Ok(test)
        }
    }
}

fn main() {
    let args = Cli::parse();

    let fp = args.path;

    println!("processing file: {}", fp.display());
    let _ = process_file(fp.clone());
}
