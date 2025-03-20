#include "../src/casm.h"
#include <stdio.h>

int
main(void)
{
	struct lexer lex;
	struct token tok;

	lex = lexer_new(fopen("test/add.s", "r"));

	for (tok = lexer_token(&lex);
	     tok.type != TOKEN_EOF;
	     tok = lexer_token(&lex)) {
	     	if (tok.str[0] != '\0')
			puts(tok.str);
		else
			printf("%c\n", tok.type);
	}

	return 0;
}
