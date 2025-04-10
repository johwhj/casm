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

#ifndef _PARSER_H
#define _PARSER_H

#define MAX_KID 4

#include "lexer.h"
#include <stddef.h>

enum node_type {
	/* Node types with token */
	NODE_INT,      /* char, short, int, long */
	NODE_FLT,      /* float, double */
	NODE_STR,      /* NUL terminated C string */
	NODE_ADD,      /* + in memory addressing */
	NODE_SUB,      /* - in memory addressing */
	NODE_MUL,      /* * in memory addressing */
	NODE_TYPE,     /* variable, function, argument type */
	NODE_NAME,     /* variable, function, argument name */
	NODE_LABEL,
	NODE_ASSIGN,   /* `=` in initialized global variable */
	NODE_OPCODE,   /* CPU dependent */
	NODE_REGISTER, /* CPU dependent */

	/* Node types without token */
	NODE_ADDRESS,  /* such as [reg + num] */
	NODE_ARGUMENT, /* has NODE_TYPE and NODE_NAME as children */
	NODE_FUNCTION, /* has NODE_TYPE and NODE_NAME as children */
	NODE_VARIABLE, /* has NODE_TYPE and NODE_NAME as children */
	NODE_INSTRUCTION,
	NODE_ROOT
};

struct node {
	const char *str;
	enum node_type type;
	struct node *kid[MAX_KID];
	size_t col, row, len;
};

struct parser {
	const char **opt, **reg; /* operators and registers */
};

struct parser parser_new(const char **, const char **);
struct node *parser_ast(struct parser *, struct lexer *);
void parser_free(struct parser *);

#endif
