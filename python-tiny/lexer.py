from ast import Set


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
  def abort(self, message):
    if self.curChar not in self.valid_strings:
      print(message)
      exit(-1)
    

  # skip whitespace except newlines, which we will use to indicate end of statement
  def skipWhitespace(self):
    while self.curChar == ' ':
      self.nextChar()

  # skip comments in the code
  def skipComments(self):
    pass

  # return in next token
  def getToken(self):
    self.peek()
    self.nextChar()
    return self.curChar

