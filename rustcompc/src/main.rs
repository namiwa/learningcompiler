use rustcompc::lexer::Lexer;

fn main() {
    println!("Hello, testing mini lexer in rust!");
    let input = String::from("11 == 11");
    let mut lexer = Lexer::build_lexer(&input);
    while lexer.peek() != ('\0' as char) {
        let token = lexer.get_token();
        println!("kind: {} text: {}", token.kind, token.text);
    }
}
