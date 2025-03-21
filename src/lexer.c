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

	return skip_whitespace(cur);
}

static struct token
token_new(char *str, size_t len)
{
	struct token tok;
	size_t i;

	tok.type = TOKEN_ERROR;
	if ((tok.str = malloc(len + 1)) == NULL)
		return tok;

	(void)strncpy(tok.str, str, len);
	tok.str[len] = '\0';

	for (i = 0; type_map[i]; ++i) {
		if (strcmp(tok.str, type_map[i]) == 0) {
			tok.type = TOKEN_TYPE;
			return tok;
		}
	}

	tok.type = TOKEN_NAME;

	return tok;
}

static struct token
token_type(int type)
{
	struct token tok;

	tok.type = type;
	tok.str = NULL;

	return tok;
}

int
lexer_init(struct lexer *lex, FILE *src)
{
	char buf[BUFSIZ];
	long siz, idx;

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
	char *str;
	size_t len;

	str = lex->cur = skip_whitespace(lex->cur);
	str = lex->cur = skip_comment(lex->cur);

	if (*lex->cur == '\0')
		return token_type(TOKEN_EOF);
	if (strchr("(){}[];,=+-*/", *lex->cur))
		return token_type(*lex->cur++);
	for (len = 0; !isspace(*lex->cur); ++len) {
		if (*lex->cur == '\0')
			return token_type(TOKEN_EOF);
		if (strchr("(){}[];,=+-*/", *lex->cur))
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
