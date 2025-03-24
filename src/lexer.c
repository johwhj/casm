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
skip_whitespace(char *cur)
{
	while (isspace(*cur))
		++cur;

	return cur;
}

static char *
skip_comment(char *cur)
{
	if (cur[0] != '/')
		return cur;

	switch (cur[1]) {
	case '*': /* multiline comment */
		for (cur += 2; cur[0] != '*' || cur[1] != '/'; ++cur)
			/* ignore characters */;
		cur += 2;
		break;
	case '/': /* single line comment */
		for (cur += 2; *cur != '\n'; ++cur)
			/* ignore characters */;
		++cur;
		break;
	default:
		break;
	}

	return cur;
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
token_type(char *str)
{
	size_t i, len;

	len = strlen(str);

	if (str[len - 1] == ':')
		return TOKEN_LABEL;
	if (*str == '"' && str[len - 1] == '"')
		return TOKEN_STRING;
	if (is_integer(str))
		return TOKEN_INTEGER;
	if (is_float(str))
		return TOKEN_FLOAT;
	for (i = 0; type_map[i]; ++i)
		if (strcmp(str, type_map[i]) == 0)
			return TOKEN_TYPE;

	return TOKEN_NAME;
}

static struct token
token_new(const char *str, const size_t len)
{
	struct token tok;

	if ((tok.str = malloc(len + 1)) == NULL)
		return tok;

	(void)strncpy(tok.str, str, len);
	tok.str[len] = '\0';
	tok.type = token_type(tok.str);

	return tok;
}

static struct token
typed_token(int type)
{
	struct token tok;

	tok.type = type;
	tok.str = NULL;

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
	lex->col = lex->row = 0;

	return 0;
}

struct token
lexer_token(struct lexer *lex)
{
	char *str;
	size_t len;

	str = lex->cur = skip_whitespace(lex->cur);
	str = lex->cur = skip_comment(lex->cur);
	str = lex->cur = skip_whitespace(lex->cur);

	if (*lex->cur == '\0')
		return typed_token(TOKEN_EOF);
	if (strchr("(){}[];,=+-*", *lex->cur) && !isdigit(lex->cur[1]))
		return typed_token(*lex->cur++);
	for (len = 0; !isspace(*lex->cur); ++len) {
		if (*lex->cur == '\0')
			return typed_token(TOKEN_EOF);
		if (strchr("(){}[];,=+-*", *lex->cur) && !isdigit(lex->cur[1]))
			break;
		++lex->cur;
	}

	return token_new(str, len);
}

void
lexer_free(struct lexer *lex)
{
	if (lex->str)
		free(lex->str);

	lex->str = NULL;
	lex->col = lex->row = 0;
}
