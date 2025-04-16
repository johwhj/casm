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

#include "ast.h"
#include <stdlib.h>
#include <string.h>

struct node *
ast_new(const char **opt, const char **reg, struct lexer *lex)
{
}

void
ast_free(struct node *root)
{
	struct node *stack[32], *cur;
	size_t top, idx;

	stack[0] = root;
	top = 1;

	while (top) {
		cur = stack[--top];
		for (idx = 0; idx < cur->len; ++idx)
			stack[top++] = cur->kid[idx];

		free(cur->kid);
		free(cur);
	}
}
