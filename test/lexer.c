/*
 * CASM - C-like assembler
 *
 * Written in 2025 by Woohyun Joh <johwhj@gmail.com>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include "../src/lexer.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int
main(void)
{
	char buf[128];
	struct lexer lex;
	FILE *src;
	enum token_type type;

	src = fopen("test/add.s", "r");
	lex = lexer_new(src);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 15 && lex.row == 1);
	assert(strcmp(buf, "#") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_KEYWORD);
	assert(lex.col == 15 && lex.row == 8);
	assert(strcmp(buf, "include") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_STRING);
	assert(lex.col == 15 && lex.row == 16);
	assert(strcmp(buf, "\"add.h\"") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_KEYWORD);
	assert(lex.col == 17 && lex.row == 3);
	assert(strcmp(buf, "int") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 17 && lex.row == 9);
	assert(strcmp(buf, "_data") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 17 && lex.row == 11);
	assert(strcmp(buf, "=") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 17 && lex.row == 13);
	assert(strcmp(buf, "-") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_NUMBER);
	assert(lex.col == 17 && lex.row == 14);
	assert(strcmp(buf, "1") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 17 && lex.row == 15);
	assert(strcmp(buf, ";") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_KEYWORD);
	assert(lex.col == 18 && lex.row == 3);
	assert(strcmp(buf, "int") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 18 && lex.row == 8);
	assert(strcmp(buf, "_bss") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 18 && lex.row == 9);
	assert(strcmp(buf, ";") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_KEYWORD);
	assert(lex.col == 20 && lex.row == 3);
	assert(strcmp(buf, "int") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 21 && lex.row == 3);
	assert(strcmp(buf, "add") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 21 && lex.row == 4);
	assert(strcmp(buf, "(") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_KEYWORD);
	assert(lex.col == 21 && lex.row == 7);
	assert(strcmp(buf, "int") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 21 && lex.row == 9);
	assert(strcmp(buf, "x") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 21 && lex.row == 10);
	assert(strcmp(buf, ",") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_KEYWORD);
	assert(lex.col == 21 && lex.row == 14);
	assert(strcmp(buf, "int") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 21 && lex.row == 16);
	assert(strcmp(buf, "y") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 21 && lex.row == 17);
	assert(strcmp(buf, ")") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 22 && lex.row == 1);
	assert(strcmp(buf, "{") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 23 && lex.row == 4);
	assert(strcmp(buf, "test") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 23 && lex.row == 5);
	assert(strcmp(buf, ":") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 24 && lex.row == 11);
	assert(strcmp(buf, "mov") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 24 && lex.row == 15);
	assert(strcmp(buf, "eax") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 24 && lex.row == 16);
	assert(strcmp(buf, ",") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 24 && lex.row == 18);
	assert(strcmp(buf, "x") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 24 && lex.row == 19);
	assert(strcmp(buf, ";") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 25 && lex.row == 11);
	assert(strcmp(buf, "add") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 25 && lex.row == 15);
	assert(strcmp(buf, "eax") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 25 && lex.row == 16);
	assert(strcmp(buf, ",") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 25 && lex.row == 18);
	assert(strcmp(buf, "y") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 25 && lex.row == 19);
	assert(strcmp(buf, ";") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_IDENT);
	assert(lex.col == 27 && lex.row == 11);
	assert(strcmp(buf, "ret") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 27 && lex.row == 12);
	assert(strcmp(buf, ";") == 0);

	type = lexer_next(&lex, buf, sizeof(buf));
	assert(type == TOKEN_PUNCT);
	assert(lex.col == 28 && lex.row == 1);
	assert(strcmp(buf, "}") == 0);

	return 0;
}
