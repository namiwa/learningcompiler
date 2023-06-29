#[cfg(test)]
mod tests {
    use rustcompc::lexer::*;

    fn lexer_tester(test_statement: String, valid_tokens: Vec<TokenType>, print_tokens: bool) {
        let mut lexer = Lexer::build_lexer(&test_statement);
        let mut index = 0;

        while index < valid_tokens.len() {
            let token = lexer.get_token();
            if print_tokens {
                println!("{}", token);
            }
            assert_eq!(token.kind, valid_tokens[index]);
            index += 1;
        }
    }

    #[test]
    fn it_parses_tokens() {
        let test_statement = String::from("##+- # This is a comment!\n * + ");
        let valid_tokens = vec![TokenType::ASTERISK, TokenType::PLUS];
        lexer_tester(test_statement, valid_tokens, false);
    }

    #[test]
    fn it_parses_strings() {
        let test_statement = String::from("\"testing str\"");
        let valid_tokens = vec![TokenType::STRING];
        lexer_tester(test_statement, valid_tokens, false)
    }

    #[test]
    fn it_parses_numbers() {
        let test_statement = String::from("12.34 * 456");
        let valid_tokens = vec![TokenType::NUMBER, TokenType::ASTERISK, TokenType::NUMBER];
        lexer_tester(test_statement, valid_tokens, false);

        let test_statement = String::from("1234 + 6");
        let valid_tokens = vec![TokenType::NUMBER, TokenType::PLUS, TokenType::NUMBER];
        lexer_tester(test_statement, valid_tokens, false);

        let test_statement = String::from("445 1122");
        let valid_tokens = vec![TokenType::NUMBER, TokenType::NUMBER];
        lexer_tester(test_statement, valid_tokens, false);
    }

    #[test]
    fn it_parses_basic_operators() {
        let test_statement = String::from("+- */ > <\0");
        let valid_tokens = vec![
            TokenType::PLUS,
            TokenType::MINUS,
            TokenType::ASTERISK,
            TokenType::SLASH,
            TokenType::GT,
            TokenType::LT,
            TokenType::EOF,
        ];
        lexer_tester(test_statement, valid_tokens, false)
    }

    #[test]
    fn it_parses_complex_operators() {
        let test_statement = String::from("<= >= != ==");
        let valid_tokens = vec![
            TokenType::LTEQ,
            TokenType::GTEQ,
            TokenType::NOTEQ,
            TokenType::EQEQ,
        ];
        lexer_tester(test_statement, valid_tokens, false)
    }

    #[test]
    fn it_parses_keywords() {
        let test_statement = String::from("LET IF THEN ELSE");
        let valid_tokens = vec![
            TokenType::LET,
            TokenType::IF,
            TokenType::THEN,
            TokenType::ELSE,
        ];
        lexer_tester(test_statement, valid_tokens, false)
    }

    #[test]
    fn end_lexer_test() {
        let test_statement = String::from("IF+-123 foo*THEN/");
        let valid_tokens = vec![
            TokenType::IF,
            TokenType::PLUS,
            TokenType::MINUS,
            TokenType::NUMBER,
            TokenType::IDENT,
            TokenType::ASTERISK,
            TokenType::THEN,
            TokenType::SLASH,
        ];
        lexer_tester(test_statement, valid_tokens, true)
    }
}
