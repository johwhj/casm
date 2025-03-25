#include "../src/casm.h"
#include <stdio.h>

static int
is_printable(enum token_type type)
{
	return type == TOKEN_NAME || type == TOKEN_TYPE
	       || type == TOKEN_INTEGER || type == TOKEN_STRING
	       || type == TOKEN_FLOAT || type == TOKEN_LABEL;
}

int
main(void)
{
	struct lexer lex;
	struct token tok;
	FILE *src;

	src = fopen("test/add.s", "r");
	lexer_init(&lex, src);

	while ((tok = lexer_token(&lex)).type != TOKEN_EOF) {
		if (is_printable(tok.type))
	     		puts(tok.str);
		else
			printf("%c\n", tok.type);
	}

	return 0;
}
