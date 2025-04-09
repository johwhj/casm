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
	NODE_ADD,     /* + in memory addressing */
	NODE_SUB,     /* - in memory addressing */
	NODE_MUL,     /* * in memory addressing */
	NODE_TYPE,    /* function or argument type */
	NODE_NAME,    /* function or argument name */
	NODE_LABEL,
	NODE_ASSIGN,  /* `=` in initialized global variable */
	NODE_NUMBER,
	NODE_STRING,
	NODE_OPCODE,
	NODE_ADDRESS, /* such as [reg + num] */
	NODE_ARGUMENT,
	NODE_REGISTER,
	NODE_FUNCTION,
	NODE_VARIABLE,
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
	struct node *root;
};

struct node *ast_new(struct lexer *);
struct node *node_new(const char *, enum node_type, size_t, size_t);
void node_free(struct node *);

#endif
