#include "../src/casm.h"
#include <stdio.h>

static int
is_printable(enum token_type type)
{
	return type == TOKEN_NAME || type == TOKEN_TYPE
	       || type == TOKEN_INTEGER || type == TOKEN_STRING
	       || type == TOKEN_FLOAT || type == TOKEN_LABEL
	       || type == TOKEN_MACRO;
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
	     		printf("%s\t%d:%d\n", tok.str, tok.col, tok.row);
		else
			printf("%c\t%d:%d\n", tok.type, tok.col, tok.row);
	}

	return 0;
}
