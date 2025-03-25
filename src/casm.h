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

#ifndef _CASM_H
#define _CASM_H

#define PROGNAME "casm"
#define TOKEN_SIZE 64

#include <stdio.h>

struct casm {
	const char *name;
	FILE *src, *obj;
};

struct lexer {
	char *str, *cur;
	size_t col, row;
};

enum token_type {
	TOKEN_LPAR = '(',
	TOKEN_RPAR = ')',
	TOKEN_MUL = '*',
	TOKEN_ADD = '+',
	TOKEN_SUB = '-',
	TOKEN_COMMA = ',',
	TOKEN_SEMICOLON = ';',
	TOKEN_ASSIGN = '=',
	TOKEN_LBRACKET = '[',
	TOKEN_RBRACKET = ']',
	TOKEN_LBRACE = '{',
	TOKEN_RBRACE = '}',
	TOKEN_INTEGER,
	TOKEN_STRING,
	TOKEN_FLOAT,
	TOKEN_LABEL,
	TOKEN_TYPE,
	TOKEN_NAME, /* name of variable, function, register or operation */
	TOKEN_ERROR,
	TOKEN_EOF
};

struct token {
	char str[TOKEN_SIZE];
	enum token_type type;
	size_t col, row;
};

/* casm.c */
int casm_init(struct casm *, const char *);
void casm_free(struct casm *);

/* x86-64.c */
int codegen(struct casm *);

/* lexer.c */
int lexer_init(struct lexer *, FILE *);
struct token lexer_token(struct lexer *);
void lexer_free(struct lexer *);

/* parser.c */
/* TODO */

/* utils.c */
int usage(void);
int error(const char *, ...);

#endif
