import lexer as lex

def main():
  input = "+- # This is a comment!\n */"
  lexer = lex.Lexer(input)

  token = lexer.getToken()
  token = lexer.getToken()
  while token.kind != lex.TokenType.EOF:
    print(token.kind)
    token = lexer.getToken()

  input = "+- */"
  lexer = lex.Lexer(input)

  token = lexer.getToken()
  while token.kind != lex.TokenType.EOF:
    print(token.kind)
    token = lexer.getToken()

  input = "+- */ >>= = !="
  lexer = lex.Lexer(input)

  token = lexer.getToken()
  while token.kind != lex.TokenType.EOF:
    print(token.kind)
    token = lexer.getToken()

if __name__ == '__main__':
  main()