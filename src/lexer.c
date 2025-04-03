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

static char *keyword[] = {
	/* preprocessor keywords */
	"if",    "elif",   "else",   "endif",
	"ifdef", "ifndef", "define", "undef"
	"error", "include",

	/* type qualifiers and type modifiers */
	"const", "static", "signed", "unsigned",

	/* types */
	"char", "short", "int", "long", "float", "double",

	/* end of array */
	NULL,
};

static char *
lexer_next_chr(struct lexer *lex)
{
	if (*lex->cur == '\n') {
		lex->row = 0;
		++lex->col;
	} else if (*lex->cur == '\t') {
		lex->row += 8;
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
	int i;

	if (buf[0] == '"' && buf[strlen(buf) - 1] == '"')
		return TOKEN_STRING;
	if (sscanf(buf, "%lf", &f) == 1)
		return TOKEN_NUMBER;
	if (*buf != '_' && !isalpha(*buf))
		return TOKEN_NONE;
	for (i = 0; keyword[i]; ++i)
		if (strcmp(keyword[i], buf) == 0)
			return TOKEN_KEYWORD;
	for (++buf; *buf; ++buf)
		if (*buf != '_' && !isalnum(*buf))
			return TOKEN_NONE;

	return TOKEN_IDENT;
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
	size_t i;

	memset(buf, '\0', siz);
	lex->cur = lexer_next_str(lex);

	if (*lex->cur == '\0')
		return TOKEN_EOF;
	if (strchr("#()*+,-:;=[]{}", *lex->cur)) {
		++lex->row;
		buf[0] = *lex->cur++;
		return TOKEN_PUNCT;
	}
	for (i = 0; i < siz; ++i) {
		if (isspace(*lex->cur) || strchr("#()*+,-:;=[]{}", *lex->cur))
			return token_type(buf);

		++lex->row;
		buf[i] = *lex->cur++;
	}

	return TOKEN_NONE;
}

void
lexer_free(struct lexer *lex)
{
	free(lex->str);
	lex->str = NULL;
}
