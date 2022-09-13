pub mod lexer;

fn main() {
    println!("Hello, testing mini lexer in rust!");
    let input = String::from("LET foobar = 123");

    let mut lexer = lexer::Lexer::build_lexer(input);

    while lexer.peek() != ('\0' as char) {
      print!("{}", lexer.curr_char);
      lexer.next_char();
    }
}
