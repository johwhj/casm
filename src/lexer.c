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

#include "casm.h"
#include <ctype.h>
#include <string.h>

static const char *type_map[] = {
	"char", "short", "int", "long", "unsigned",
	"float", "double", NULL
};

static struct token
token_new(int type_chr)
{
	struct token tok;

	tok.type = type_chr;
	(void)memset(tok.str, '\0', sizeof(tok.str));

	return tok;
}

static enum token_type
token_type(const char *str)
{
	size_t i;

	for (i = 0; type_map[i]; ++i)
		if (strcmp(str, type_map[i]) == 0)
			return TOKEN_TYPE;

	return TOKEN_NAME;
}

struct lexer
lexer_new(FILE *src)
{
	struct lexer lex;

	lex.src = src;
	lex.col = lex.row = 0;

	return lex;
}

struct token
lexer_token(struct lexer *lex)
{
	static char delim = '\0';
	struct token tok;
	size_t len;
	int chr;

	if (delim) {
		tok = token_new(delim);
		delim = '\0';
		return tok;
	}

	while (isspace(chr = fgetc(lex->src)))
		/* skip whitespaces */;
	for (len = 0; len < BUF_SIZE && !isspace(chr); ++len) {
		tok.str[len] = chr;
		if (feof(lex->src))
			return token_new(TOKEN_EOF);
		if (ferror(lex->src))
			return token_new(TOKEN_ERROR);
		if (strchr(",;(){}[]=*+-", chr)) {
			if (tok.str[0] != '\0')
				return token_new(chr);

			delim = chr;
			break;
		}

		chr = fgetc(lex->src);
	}

	tok.str[len] = '\0';
	tok.type = token_type(tok.str);

	return tok;
}
