
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

pub struct Token {
  pub text: char,
  pub kind: char,
}

impl Token {
  pub fn new (mut self, token_text: char , token_kind: char) {
    self.text = token_text;
    self.kind = token_kind;
  }
}


enum TokenType {
  EOF = -1,
	NEWLINE = 0,
	NUMBER = 1,
	IDENT = 2,
	STRING = 3,
	// Keywords.
	LABEL = 101,
	GOTO = 102,
	PRINT = 103,
	INPUT = 104,
	LET = 105,
	IF = 106,
	THEN = 107,
	ENDIF = 108,
	WHILE = 109,
	REPEAT = 110,
	ENDWHILE = 111,
	// Operators.
	EQ = 201,
	PLUS = 202,
	MINUS = 203,
	ASTERISK = 204,
	SLASH = 205,
	EQEQ = 206,
	NOTEQ = 207,
	LT = 208,
	LTEQ = 209,
	GT = 210,
	GTEQ = 211
}
