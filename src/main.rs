extern crate libbrainrs;

use std::io;
use std::io::Write;
use std::io::Read;
use std::fs::File;

use std::env::args;

use libbrainrs::interpreter::*;
use libbrainrs::parser::*;

fn cli_interpret() {
    let mut line = String::new();
    let mut tmpline = String::new();

    let mut st = State::new();

    loop {
        print!("> ");
        let _ = io::stdout().flush();
        match std::io::stdin().read_line(&mut tmpline) {
            Ok(_) => {
                if tmpline == "quit" {
                    break;
                }

                line = line + &tmpline;

                if !tmpline.ends_with("\\") {
                    let ts = parse(&line).ok().unwrap();
                    interpret(&ts, &mut st);
                    line.clear();
                }
            },
            Err(_) => break
        }
    }
}

fn file_interpreter(path: &str) {

    match File::open(path) {
        Ok(ref mut f) => {
            let mut buf: Vec<u8> = vec![];

            match f.read_to_end(&mut buf) {
                Ok(_) => {
                    let source = String::from_utf8(buf).unwrap();
                    
                    let mut state = State::new();

                    match parse(&source) {
                        Ok(ref ts) => interpret(&ts, &mut state),
                        Err(err) => println!("Error {:?}", err)
                    };
                },
                _ => {
                    println!("Error reading {}", path);
                }
            };
        },
        Err(_) => {
            println!("Unable to open {}", path);
        }
    };
}

fn main() {
    let mut cli = true;

    for f in args().skip(1) {
        cli = false;
        file_interpreter(&f);
    }

    if cli {
        cli_interpret();
    }

}
