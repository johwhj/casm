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
#include <stdlib.h>
#include <string.h>

static const char *type_map[] = {
	"char", "short", "int", "long", "unsigned",
	"float", "double",
	NULL
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

	return TOKEN_UNKNOWN;
}

int
lexer_init(struct lexer *lex, FILE *src)
{
	char buf[BUFSIZ];
	size_t siz, idx;

	if (fseek(src, 0, SEEK_END))
		return -1;
	if ((siz = ftell(src)) < 0)
		return -1;
	if ((lex->str = malloc(siz + 1)) == NULL)
		return -1;

	rewind(src);
	for (idx = 0; idx < siz; idx += siz)
		siz = fread(lex->str + idx, sizeof(char), sizeof(buf), src);

	lex->str[idx] = '\0';
	lex->cur = lex->str;
	lex->col = lex->row = 0;

	return 0;
}

struct token
lexer_token(struct lexer *lex)
{
}

void
lexer_free(struct lexer *lex)
{
	if (lex->str)
		free(lex->str);

	lex->str = NULL;
	lex->col = lex->row = 0;
}
