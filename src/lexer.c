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
	"char", "short", "int", "long", "unsigned", "float", "double", NULL
};

static char *
lexer_next(struct lexer *lex)
{
	if (*lex->cur == '\n') {
		++lex->col;
		lex->row = 0;
	}

	++lex->cur;
	++lex->row;

	return lex->cur;
}

static char *
skip_meaningless(struct lexer *lex)
{
	while (isspace(*lex->cur))
		lexer_next(lex);
	if (lex->cur[0] != '/')
		return lex->cur;
	if (lex->cur[1] == '*') {
		lex->cur += 2;
		while (lex->cur[0] != '*' || lex->cur[1] != '/')
			lexer_next(lex);
		lex->cur += 2;
	} else if (lex->cur[1] == '/') {
		lex->cur += 2;
		while (lex->cur[0] != '\n')
			lexer_next(lex);
		++lex->cur;
	}
	while (isspace(*lex->cur))
		lexer_next(lex);

	return lex->cur;
}

static int
is_integer(const char *str)
{
	unsigned long i;

	if (str[0] != '0' || str[1] != 'b')
		return sscanf(str, "%lu", &i) == 1;
	for (str += 2; *str; ++str)
		if (*str != '0' && *str != '1')
			return 0;

	return 1;
}

static int
is_float(const char *str)
{
	double f;

	return sscanf(str, "%lf", &f) == 1;
}

static enum token_type
token_type(char *str, const size_t len)
{
	size_t i;

	if (*str == '#')
		return TOKEN_MACRO;
	if (*str == '"' && str[len - 1] == '"')
		return TOKEN_STRING;
	if (is_integer(str))
		return TOKEN_INTEGER;
	if (is_float(str))
		return TOKEN_FLOAT;
	for (i = 0; type_map[i]; ++i)
		if (strncmp(str, type_map[i], len) == 0)
			return TOKEN_TYPE;
	if (str[len - 1] == ':') {
		str[len - 1] = '\0';
		return TOKEN_LABEL;
	}

	return TOKEN_NAME;
}

static struct token
token_new(struct lexer *lex, const enum token_type type,
          char *str, const size_t len)
{
	struct token tok;

	tok.type = (type == TOKEN_NONE) ? token_type(str, len) : type;
	memcpy(tok.str, str, len);
	tok.str[len] = '\0';

	tok.col = lex->col;
	tok.row = lex->row - len;

	return tok;
}

int
lexer_init(struct lexer *lex, FILE *src)
{
	long siz;

	if (fseek(src, 0, SEEK_END))
		return -1;
	if ((siz = ftell(src)) < 0)
		return -1;
	if ((lex->str = malloc(siz + 1)) == NULL)
		return -1;

	rewind(src);
	if (fread(lex->str, sizeof(char), siz, src) < (size_t)siz)
		return -1;

	lex->str[siz] = '\0';
	lex->cur = lex->str;
	lex->col = lex->row = 1;

	return 0;
}

struct token
lexer_token(struct lexer *lex)
{
	char *str;
	size_t len;

	str = skip_meaningless(lex);

	if (*str == '\0')
		return token_new(lex, TOKEN_EOF, NULL, 0);
	if (strchr("(){}[];,=+-*", *str) && !isdigit(str[1]))
		return token_new(lex, *str, lexer_next(lex), 1);
	for (len = 0; !isspace(*lex->cur); ++len) {
		if (*lex->cur == '\0')
			break;
		if (strchr("(){}[];,=+-*", *lex->cur) && !isdigit(lex->cur[1]))
			break;

		lexer_next(lex);
	}

	return token_new(lex, TOKEN_NONE, str, len);
}

void
lexer_free(struct lexer *lex)
{
	if (lex->str)
		free(lex->str);

	lex->str = lex->cur = NULL;
	lex->col = lex->row = 0;
}
