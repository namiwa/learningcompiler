use rustcompc::Lexer;

fn main() {
    println!("Hello, testing mini lexer in rust!");
    let input = String::from("LET foobar = 123");
    let mut lexer = Lexer::build_lexer(&input);
    let token = lexer.get_token();
    while lexer.peek() != ('\0' as char) {
        print!("{}", lexer.curr_char);
        print!("{}", token.kind);
        lexer.get_token();
    }
}
