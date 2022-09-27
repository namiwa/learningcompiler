use rustcompc;

#[cfg(test)]
fn it_parses_tokens() {
  let test_statement = String::from("+- *");
  let valid_tokens = vec![
    rustcompc::TokenType::PLUS,
  ];
}