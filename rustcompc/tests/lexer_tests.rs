#[cfg(test)]
mod tests {
  use rustcompc::TokenType;
  use rustcompc::Lexer;

  #[test]
  fn it_parses_tokens() {
    let test_statement = String::from("+- # This is a comment!\n */");
    let valid_tokens = vec![
      TokenType::PLUS,
      TokenType::MINUS,
      TokenType::NEWLINE,
      TokenType::ASTERISK,
      TokenType::SLASH,
      TokenType::NEWLINE
    ];
  
    let mut lexer = Lexer::build_lexer(test_statement);
    let mut index = 0;

    // lexer tokens are read from back to front
    while index < valid_tokens.len() && lexer.get_token().kind != TokenType::EOF {
      let token = lexer.get_token();
      println!("comparing: {} to {}", token.kind, valid_tokens[index]);
      assert_eq!(token.kind, valid_tokens[index]);
      index += 1;
    }
  }
}