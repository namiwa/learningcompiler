#[cfg(test)]
mod tests {
    use rustcompc::Lexer;
    use rustcompc::TokenType;

    fn lexer_tester(test_statement: String, valid_tokens: Vec<TokenType>) {
        let mut lexer = Lexer::build_lexer(test_statement);
        let mut index = 0;

        // lexer tokens are read from back to front
        while index < valid_tokens.len() {
            let token = lexer.get_token();
            assert_eq!(token.kind, valid_tokens[index]);
            index += 1;
        }
    }

    #[test]
    fn it_parses_tokens() {
        let test_statement = String::from("##+- # This is a comment!\n * + ");
        let valid_tokens = vec![TokenType::ASTERISK, TokenType::PLUS];
        lexer_tester(test_statement, valid_tokens);
    }

    #[test]
    fn it_parses_strings() {
        let test_statement = String::from("\"testing str\"");
        let valid_tokens = vec![TokenType::STRING, TokenType::EOF];
        lexer_tester(test_statement, valid_tokens)
    }
}
