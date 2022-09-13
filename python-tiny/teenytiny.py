import lexer as lex

def main():
	input = "LET foobar = 123"
	lexer = lex.Lexer(input)

	while lexer.peek() != '\0':
		print(lexer.curChar)
		lexer.nextChar()

if __name__ == '__main__':
  main()