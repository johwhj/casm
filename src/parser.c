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

#include "parser.h"
#include <stdlib.h>

struct node *
node_new(const char *str, enum node_type type, size_t col, size_t row)
{
	struct node *new;
	size_t len;

	if ((new = malloc(sizeof(struct node))) == NULL)
		return NULL;
	if ((new->str = malloc((len = strlen(str)) + 1)) == NULL)
		return NULL;

	strncpy(new->str, str, len);
	new->type = type;
	new->col = col;
	new->row = row;

	return new;
}

void
node_free(struct node *node)
{
	size_t i;

	if (node == NULL)
		return;
	for (i = 0; i < node->len; ++i)
		node_free(node->kid[i]);

	free(node);
}
