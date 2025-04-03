#include "../src/lexer.h"
#include <stdio.h>

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
		printf("[%d]:%2d:%2d:%s\n", type, lex.col, lex.row, buf);

	return 0;
}
