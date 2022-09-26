use std::{fmt, default};


// Define our error types. These may be customized for our error handling cases.
// Now we will be able to write our own errors, defer to an underlying error
// implementation, or do something in between.
#[derive(Debug, Clone)]
struct LexerError {
  msg: String
}

type Result<'a, T> = std::result::Result<T, LexerError>;

// Generation of an error is completely separate from how it is displayed.
// There's no need to be concerned about cluttering complex logic with the display style.
//
// Note that we don't store any extra info about the errors. This means we can't state
// which string failed to parse without modifying our types to carry that information.
impl fmt::Display for LexerError {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
      write!(f, "Lexer Error: invalid token {}", self.msg)
  }
}

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

  pub fn next_char(&mut self) -> char {
    if self.cur_pos >= self.source.len() {
      self.curr_char = '\0';
    } else {
      self.cur_pos =  self.cur_pos + 1;
      let byte = self.source.as_bytes()[self.cur_pos];
      self.curr_char = byte as char;
    }
    self.curr_char
  }

  pub fn peek(&mut self) -> char {
    if self.cur_pos + 1 >= self.source.len() {
      return '\0'
    }

    let byte = self.source.as_bytes()[self.cur_pos + 1];
    self.curr_char = byte as char;
    return self.curr_char
  }
  
  fn skip_whitespace(&mut self) {
    while self.curr_char == ' ' || self.curr_char == '\t' || self.curr_char == '\r' {
      self.next_char();
    }
  }

  fn skip_comments(&mut self) {
    if self.curr_char == '#' {
      while self.curr_char != '\n' {
        self.next_char();
      }
    }
  }

  pub fn get_token(&mut self) -> Token {
    self.skip_comments();
    self.skip_whitespace();
    let token: Result<Token> = match self.next_char() {
      '+' => Ok(Token { text: self.curr_char.to_string(), kind: TokenType::PLUS }),
      '-' => Ok(Token { text: self.curr_char.to_string(), kind: TokenType::MINUS }),
      '*' => Ok(Token { text: self.curr_char.to_string(), kind: TokenType::ASTERISK }),
      '/' => Ok(Token { text: self.curr_char.to_string(), kind: TokenType::SLASH }),
      '\n' => Ok(Token { text: self.curr_char.to_string(), kind: TokenType::NEWLINE }),
      '\0' => Ok(Token { text: self.curr_char.to_string(), kind: TokenType::EOF }),
      '=' => {
        match self.peek() {
            '=' => {
              self.next_char();
              Ok(Token { text: self.curr_char.to_string(), kind: TokenType::EQEQ})
            }
            _ => Ok(Token { text: self.curr_char.to_string(), kind: TokenType::EQ }),
        }
      },
      '>' => {
        match self.peek() {
            '=' => {
              self.next_char();
              Ok(Token { text: self.curr_char.to_string(), kind: TokenType::GTEQ})
            }
            _ => Ok(Token { text: self.curr_char.to_string(), kind: TokenType::GT }),
        }
      },
      '<' => {
        match self.peek() {
            '=' => {
              self.next_char();
              Ok(Token { text: self.curr_char.to_string(), kind: TokenType::LTEQ})
            }
            _ => Ok(Token { text: self.curr_char.to_string(), kind: TokenType::LT }),
        }
      },
      '!' => {
        match self.peek() {
            '=' => {
              self.next_char();
              Ok(Token { text: self.curr_char.to_string(), kind: TokenType::NOTEQ})
            }
            _ => Err(LexerError { msg: String::from("! not valid without =") }),
        }
      },
      '\"' => {
        self.next_char();
        let start_pos = self.cur_pos;

        while self.curr_char != '\"' {
          let val = match self.curr_char {
            '\r' => Err(LexerError { msg: String::from("invalid tab character")}),
            '\n' => Err(LexerError { msg: String::from("invalid charridge character")}),
            '\t' => Err(LexerError { msg: String::from("invalid tab character")}),
            '\\' => Err(LexerError { msg: String::from("invalid slash character")}),
            '%' => Err(LexerError { msg: String::from("invalid percentage character")}),
            _default => {
              self.next_char();
              Ok(self.curr_char)
            },
          };
          val.unwrap();
        };
        let tok_text = self.source.get_mut(start_pos..self.cur_pos).unwrap();
        Ok(Token { text: String::from(tok_text), kind: TokenType::STRING })
      }
      _ => Err(LexerError { msg: String::from("unknown token") }),
    };
    self.next_char();
    token.unwrap()
  } 
}

pub struct Token {
  pub text: String,
  pub kind: TokenType,
}

pub enum TokenType {
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
