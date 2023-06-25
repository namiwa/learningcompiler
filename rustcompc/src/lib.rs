// based on tiny lexer tutorial in python from  
use std::fmt;

// Define our error types. These may be customized for our error handling cases.
// Now we will be able to write our own errors, defer to an underlying error
// implementation, or do something in between.
#[derive(Debug, Clone)]
pub struct LexerError {
    msg: String,
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
            cur_pos: 0,
        }
    }

    pub fn next_char(&mut self) -> char {
        if self.cur_pos >= self.source.len() {
            self.curr_char = '\0';
        } else {
            self.curr_char = self.source.chars().nth(self.cur_pos).unwrap();
            self.cur_pos = self.cur_pos + 1;
        }
        self.curr_char
    }

    pub fn peek(&mut self) -> char {
        if self.cur_pos + 1 >= self.source.len() {
            return '\0';
        }

        let byte = self.source.as_bytes()[self.cur_pos + 1];
        self.curr_char = byte as char;
        return self.curr_char;
    }

    pub fn skip_whitespace(&mut self) {
        while self.curr_char.is_whitespace() {
            self.next_char();
        }
    }

    pub fn skip_comments(&mut self) {
        if self.curr_char == '#' {
            while self.curr_char != '\n' {
                self.next_char();
            }
        }
    }

    pub fn get_token(&mut self) -> Token {
        self.next_char();
        self.skip_comments();
        self.skip_whitespace();
        let token: Result<Token> = match self.curr_char {
            '+' => Ok(Token {
                text: self.curr_char.to_string(),
                kind: TokenType::PLUS,
            }),
            '-' => Ok(Token {
                text: self.curr_char.to_string(),
                kind: TokenType::MINUS,
            }),
            '*' => Ok(Token {
                text: self.curr_char.to_string(),
                kind: TokenType::ASTERISK,
            }),
            '/' => Ok(Token {
                text: self.curr_char.to_string(),
                kind: TokenType::SLASH,
            }),
            '\n' => Ok(Token {
                text: self.curr_char.to_string(),
                kind: TokenType::NEWLINE,
            }),
            '\0' => Ok(Token {
                text: self.curr_char.to_string(),
                kind: TokenType::EOF,
            }),
            '=' => match self.peek() {
                '=' => {
                    self.next_char();
                    Ok(Token {
                        text: self.curr_char.to_string(),
                        kind: TokenType::EQEQ,
                    })
                }
                _ => Ok(Token {
                    text: self.curr_char.to_string(),
                    kind: TokenType::EQ,
                }),
            },
            '>' => match self.peek() {
                '=' => {
                    self.next_char();
                    Ok(Token {
                        text: self.curr_char.to_string(),
                        kind: TokenType::GTEQ,
                    })
                }
                _ => Ok(Token {
                    text: self.curr_char.to_string(),
                    kind: TokenType::GT,
                }),
            },
            '<' => match self.peek() {
                '=' => {
                    self.next_char();
                    Ok(Token {
                        text: self.curr_char.to_string(),
                        kind: TokenType::LTEQ,
                    })
                }
                _ => Ok(Token {
                    text: self.curr_char.to_string(),
                    kind: TokenType::LT,
                }),
            },
            '!' => match self.peek() {
                '=' => {
                    self.next_char();
                    Ok(Token {
                        text: self.curr_char.to_string(),
                        kind: TokenType::NOTEQ,
                    })
                }
                _ => Err(LexerError {
                    msg: String::from("! not valid without ="),
                }),
            },
            '\"' => {
                self.next_char();
                let start_pos = match self.cur_pos {
                    0 => { 0 },
                    _ => { self.cur_pos - 1 } 
                };

                while self.curr_char != '\"' {
                    let val = match self.curr_char {
                        '\r' => Err(LexerError {
                            msg: String::from("invalid tab character"),
                        }),
                        '\n' => Err(LexerError {
                            msg: String::from("invalid charridge character"),
                        }),
                        '\t' => Err(LexerError {
                            msg: String::from("invalid tab character"),
                        }),
                        '\\' => Err(LexerError {
                            msg: String::from("invalid slash character"),
                        }),
                        '%' => Err(LexerError {
                            msg: String::from("invalid percentage character"),
                        }),
                        _ => {
                            self.next_char();
                            Ok(self.curr_char)
                        }
                    };
                    val.unwrap();
                }
                let tok_text = self.source.get_mut(start_pos..self.cur_pos-1).unwrap();
                Ok(Token {
                    text: String::from(tok_text),
                    kind: TokenType::STRING,
                })
            },
            c if c.is_ascii_digit() => {
                let start_pos = match self.cur_pos {
                    0 => {
                        0
                    },
                    _ => {
                        self.cur_pos - 1
                    }
                };
                while self.peek().is_ascii_digit() {
                    self.next_char();
                }
                if self.peek() == '.' {
                    self.next_char();
                    if !self.peek().is_ascii_digit() {
                        let val = Err(LexerError { 
                            msg: format!("Illegal char in number")  
                        });
                        val.unwrap()
                    }
                }
                while self.peek().is_ascii_digit() {
                    self.next_char();
                }
                let number_text = &self.source[start_pos..self.cur_pos + 1].to_string();
                self.next_char();
                Ok(Token {
                    text: number_text.to_string(),
                    kind: TokenType::NUMBER
                })
            },
            c if c.is_ascii_alphabetic() => {
                let start_pos = match self.cur_pos {
                    0 => {
                        0
                    },
                    _ => {
                        self.cur_pos - 1
                    }
                };
                while self.peek().is_ascii_alphabetic() {
                    self.next_char();
                };
                let token_text = &self.source[start_pos..self.cur_pos+1].to_string();
                let is_keyword = TokenType::get_keyword_type(token_text.clone());
                if is_keyword != TokenType::UNKNOWN {
                    self.next_char();
                    Ok(Token {
                        text: token_text.clone(),
                        kind: is_keyword
                    })
                } else {
                    Err(LexerError { 
                        msg: format!("unknown keyword encountered {}", token_text.to_string()) 
                    })
                }
            }
            unknown => Err(LexerError {
                msg: format!("unknown token: {:x}", unknown as u32),
            }),
        };
        token.unwrap()
    }
}

pub struct Token {
    pub text: String,
    pub kind: TokenType,
}

impl fmt::Display for Token {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "({} {})", self.text, self.kind)
    }
}

#[derive(PartialEq, Debug)]
pub enum TokenType {
    EOF = -1,
    NEWLINE = 0,
    NUMBER = 1,
    INDENT = 2,
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
    GTEQ = 211,

    // unknown
    UNKNOWN = 999
}

impl TokenType {
    pub fn get_keyword_type(token_text: String) -> TokenType {
        match token_text {
            c if c == String::from("LABEL") => TokenType::LABEL,
            c if c == String::from("GOTO") => TokenType::GOTO,
            c if c == String::from("PRINT") => TokenType::PRINT,
            c if c == String::from("INPUT") => TokenType::INPUT,
            c if c == String::from("IF") => TokenType::IF,
            c if c == String::from("THEN") => TokenType::THEN,
            c if c == String::from("WHILE") => TokenType::WHILE,
            c if c == String::from("REPEAT") => TokenType::REPEAT,
            c if c == String::from("ENDWHILE") => TokenType::ENDWHILE,
            c if c == String::from("LET") => TokenType::LET,
            c if c.contains(char::is_whitespace) => TokenType::INDENT,
            _ => TokenType::UNKNOWN
        }
    }
}

impl fmt::Display for TokenType {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match &*self {
            TokenType::EOF => write!(f, "EOF"),
            TokenType::NEWLINE => write!(f, "NEWLINE"),
            TokenType::NUMBER => write!(f, "NUMBER"),
            TokenType::INDENT => write!(f, "INDENT"),
            TokenType::STRING => write!(f, "STRING"),
            TokenType::LABEL => write!(f, "LABEL"),
            TokenType::GOTO => write!(f, "GOTO"),
            TokenType::PRINT => write!(f, "PRINT"),
            TokenType::INPUT => write!(f, "INPUT"),
            TokenType::LET => write!(f, "LET"),
            TokenType::IF => write!(f, "IF"),
            TokenType::THEN => write!(f, "THEN"),
            TokenType::ENDIF => write!(f, "ENDIF"),
            TokenType::WHILE => write!(f, "WHILE"),
            TokenType::REPEAT => write!(f, "REPEAT"),
            TokenType::ENDWHILE => write!(f, "ENDWHILE"),
            TokenType::EQ => write!(f, "EQ"),
            TokenType::PLUS => write!(f, "PLUS"),
            TokenType::MINUS => write!(f, "MINUS"),
            TokenType::ASTERISK => write!(f, "ASTERISK"),
            TokenType::SLASH => write!(f, "SLASH"),
            TokenType::EQEQ => write!(f, "EQEQ"),
            TokenType::NOTEQ => write!(f, "NOTEQ"),
            TokenType::LT => write!(f, "LT"),
            TokenType::LTEQ => write!(f, "LTEQ"),
            TokenType::GT => write!(f, "GT"),
            TokenType::GTEQ => write!(f, "GTEQ"),
            TokenType::UNKNOWN => write!(f, "UNKNOWN")
        }
    }
}
