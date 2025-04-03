#include "../src/lexer.h"
#include <stdio.h>

static char *
type_str(enum token_type type)
{
	switch (type) {
	case TOKEN_IDENT:
		return "TOKEN_IDENT";
	case TOKEN_PUNCT:
		return "TOKEN_PUNCT";
	case TOKEN_STRING:
		return "TOKEN_STRING";
	case TOKEN_NUMBER:
		return "TOKEN_NUMBER";
	case TOKEN_KEYWORD:
		return "TOKEN_KEYWORD";
	case TOKEN_NONE:
		return "TOKEN_NONE";
	case TOKEN_EOF:
		return "TOKEN_EOF";
	}
}

int
main(void)
{
	char buf[128];
	struct lexer lex;
	FILE *src;
	enum token_type type;

	src = fopen("test/add.s", "r");
	lex = lexer_new(src);

	while ((type = lexer_next(&lex, buf, sizeof(buf))) != TOKEN_EOF)
		printf("%-13s:%2d:%2d: %s\n",
		       type_str(type), lex.col, lex.row, buf);

	return 0;
}
