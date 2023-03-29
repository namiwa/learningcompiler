#[cfg(test)]
mod tests {
  fn it_parses_tokens() {
    let test_statement = String::from("+- *");
    let valid_tokens = vec![
      rustcompc::TokenType::PLUS,
      rustcompc::TokenType::MINUS,
      rustcompc::TokenType::ASTERISK
    ];
  
    let lexer = rustcompc::Lexer::build_lexer(test_statement);
    let token = lexer.get_token();
    let arr = Vec::new();
    while token.kind != rustcompc::TokenType::EOF {
      print(token);
      token = lexer.get_token();
      arr.push(token);
    }
    assert_eq!(arr, valid_tokens);
  }
}