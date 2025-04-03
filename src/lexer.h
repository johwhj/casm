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

#ifndef _LEXER_H
#define _LEXER_H

#include <stdio.h>

struct lexer {
	char *str, *cur;
	size_t col, row;
};

enum token_type {
	TOKEN_IDENT,
	TOKEN_PUNCT,
	TOKEN_STRING,
	TOKEN_NUMBER,
	TOKEN_KEYWORD,
	TOKEN_NONE,
	TOKEN_EOF
};

struct lexer lexer_new(FILE *);
enum token_type lexer_next(struct lexer *, char *, size_t);

#endif
