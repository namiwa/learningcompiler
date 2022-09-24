from ast import Set
import enum
import sys

class Lexer:

  valid_strings = set([])

  def __init__(self, input):
    self.source = input + '\n'
    self.curChar = ''
    self.curPos = -1
    self.nextChar()

  # process next char
  def nextChar(self):
    self.curPos += 1
    if self.curPos >= len(self.source):
      self.curChar = '\0'
    else:
      self.curChar = self.source[self.curPos]

  # return the lookahead char
  def peek(self):
    if self.curPos + 1 >= len(self.source):
      return '\0'
      
    return self.source[self.curPos + 1]

  # invalid token found, print error and exit
    # Invalid token found, print error message and exit.
  def abort(self, message):
      sys.exit("Lexing error. " + message)
    

  # skip whitespace except newlines, which we will use to indicate end of statement
  def skipWhitespace(self):
    while self.curChar == ' ' or self.curChar == '\t' or self.curChar == '\r':
        self.nextChar()

  # skip comments in the code
  def skipComments(self):
    if self.curChar == '#':
        while self.curChar != '\n':
            self.nextChar()

  # return in next token
  def getToken(self):
    self.skipWhitespace()
    self.skipComments()
    token = None

    # Check the first character of this token to see if we can decide what it is.
    # If it is a multiple character operator (e.g., !=), number, identifier, or keyword then we will process the rest.
    if self.curChar == '+':
        token = Token(self.curChar, TokenType.PLUS)
    elif self.curChar == '-':
        token = Token(self.curChar, TokenType.MINUS)
    elif self.curChar == '*':
        token = Token(self.curChar, TokenType.ASTERISK)
    elif self.curChar == '/':
        token = Token(self.curChar, TokenType.SLASH)
    elif self.curChar == '\n':
        token = Token(self.curChar, TokenType.NEWLINE)
    elif self.curChar == '\0':
        token = Token('', TokenType.EOF)
    elif self.curChar == '=':
        # Check whether this token is = or ==
        if self.peek() == '=':
            lastChar = self.curChar
            self.nextChar()
            token = Token(lastChar + self.curChar, TokenType.EQEQ)
        else:
            token = Token(self.curChar, TokenType.EQ)
    elif self.curChar == '>':
        # Check whether this is token is > or >=
        if self.peek() == '=':
            lastChar = self.curChar
            self.nextChar()
            token = Token(lastChar + self.curChar, TokenType.GTEQ)
        else:
            token = Token(self.curChar, TokenType.GT)
    elif self.curChar == '<':
            # Check whether this is token is < or <=
            if self.peek() == '=':
                lastChar = self.curChar
                self.nextChar()
                token = Token(lastChar + self.curChar, TokenType.LTEQ)
            else:
                token = Token(self.curChar, TokenType.LT)
    elif self.curChar == '!':
        if self.peek() == '=':
            lastChar = self.curChar
            self.nextChar()
            token = Token(lastChar + self.curChar, TokenType.NOTEQ)
        else:
            self.abort("Expected !=, got !" + self.peek())
    elif self.curChar == '\"':
        # Get characters between quotations.
        self.nextChar()
        startPos = self.curPos

        while self.curChar != '\"':
            # Don't allow special characters in the string. No escape characters, newlines, tabs, or %.
            # We will be using C's printf on this string.
            if self.curChar == '\r' or self.curChar == '\n' or self.curChar == '\t' or self.curChar == '\\' or self.curChar == '%':
                self.abort("Illegal character in string.")
            self.nextChar()

        tokText = self.source[startPos : self.curPos] # Get the substring.
        token = Token(tokText, TokenType.STRING)
    else:
        # Unknown token!
        self.abort("Unknown token: " + self.curChar)
  
    self.nextChar()
    return token

# Token contains the original text and the type of token.
class Token:   
  def __init__(self, tokenText, tokenKind):
      self.text = tokenText   # The token's actual text. Used for identifiers, strings, and numbers.
      self.kind = tokenKind   # The TokenType that this token is classified as.

# TokenType is our enum for all the types of tokens.
class TokenType(enum.Enum):
	EOF = -1
	NEWLINE = 0
	NUMBER = 1
	IDENT = 2
	STRING = 3
	# Keywords.
	LABEL = 101
	GOTO = 102
	PRINT = 103
	INPUT = 104
	LET = 105
	IF = 106
	THEN = 107
	ENDIF = 108
	WHILE = 109
	REPEAT = 110
	ENDWHILE = 111
	# Operators.
	EQ = 201  
	PLUS = 202
	MINUS = 203
	ASTERISK = 204
	SLASH = 205
	EQEQ = 206
	NOTEQ = 207
	LT = 208
	LTEQ = 209
	GT = 210
	GTEQ = 211