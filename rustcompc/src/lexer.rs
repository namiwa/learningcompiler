
pub struct Lexer {
  source: String,
  pub curr_char: char,
  pub cur_pos: usize,
}

impl Lexer {
  pub fn build_lexer(input: String) -> Lexer {
    Lexer {
      source: input + "\0",
      curr_char: '\0',
      cur_pos: 0
    }
  }

  pub fn next_char(&mut self) {
    if self.cur_pos >= self.source.len() {
      self.curr_char = '\0';
    } else {
      self.cur_pos =  self.cur_pos + 1;
      let byte = self.source.as_bytes()[self.cur_pos];
      self.curr_char = byte as char;
    }
  }

  pub fn peek(&mut self) -> char {
    if self.cur_pos + 1 >= self.source.len() {
      return '\0'
    }

    let byte = self.source.as_bytes()[self.cur_pos + 1];
    self.curr_char = byte as char;
    return self.curr_char
  }

  pub fn get_token(&mut self) -> char {
    self.peek();
    self.next_char();
    self.curr_char
  } 
}

