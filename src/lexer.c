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

#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static char *
lexer_next_chr(struct lexer *lex)
{
	if (*lex->cur == '\n') {
		lex->row = 1;
		++lex->col;
	} else {
		++lex->row;
	}

	return ++lex->cur;
}

static char *
lexer_next_str(struct lexer *lex)
{
	while (isspace(*lex->cur))
		lex->cur = lexer_next_chr(lex);
	if (lex->cur[0] != '/' )
		return lex->cur;
	if (lex->cur[1] == '*') {
		lex->cur += 2;
		while (lex->cur[0] != '*' || lex->cur[1] != '/')
			lex->cur = lexer_next_chr(lex);
		lex->cur += 2;
	} else if (lex->cur[1] == '/') {
		lex->cur += 2;
		while (lex->cur[0] != '\n')
			lex->cur = lexer_next_chr(lex);
		++lex->cur;
	}
	while (isspace(*lex->cur))
		lex->cur = lexer_next_chr(lex);

	return lex->cur;
}

static enum token_type
token_type(char *buf)
{
	double f;

	if (buf[0] == '"' && buf[strlen(buf) - 1] == '"')
		return TOKEN_STRING;
	if (sscanf(buf, "%lf", &f) == 1)
		return TOKEN_NUMBER;
	if (*buf != '_' && !isalpha(*buf))
		return TOKEN_NONE;
	for (++buf; *buf; ++buf)
		if (*buf != '_' && !isalnum(*buf))
			return TOKEN_NONE;

	return TOKEN_NAME;
}

struct lexer
lexer_new(FILE *src)
{
	struct lexer lex;
	long siz;

	lex.str = lex.cur = NULL;
	lex.col = lex.row = 1;

	if (fseek(src, 0, SEEK_END))
		return lex;
	if ((siz = ftell(src)) < 0)
		return lex;

	rewind(src);
	if ((lex.str = malloc(siz + 1)) == NULL)
		return lex;
	if (fread(lex.str, sizeof(char), siz, src) < (size_t)siz)
		return lex;

	lex.str[siz] = '\0';
	lex.cur = lex.str;

	return lex;
}

enum token_type
lexer_next(struct lexer *lex, char *buf, size_t siz)
{
	char *str;

	str = lexer_next_str(lex);

	if (*str == '\0')
		return TOKEN_EOF;
}
