#include "../src/casm.h"
#include <stdio.h>

int
main(void)
{
	struct lexer lex;
	struct token tok;
	FILE *src;

	src = fopen("test/add.s", "r");
	lexer_init(&lex, src);

	while ((tok = lexer_token(&lex)).type != TOKEN_EOF) {
	     	if (tok.type == TOKEN_UNKNOWN || tok.type == TOKEN_TYPE)
	     		puts(tok.str);
		else
			printf("%c\n", tok.type);
	}

	return 0;
}
