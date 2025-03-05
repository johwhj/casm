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
#include <string.h>

int
casm_init(struct casm *casm, const char *name)
{
	char *dot;

	if ((dot = strrchr(name, '.')) == NULL)
		return error("No extension: %s", name);
	if (dot[1] != 's')
		return error("Invalid extension: '%s'", name);
	if ((casm->src = fopen(name, "r")) == NULL)
		return error("No such file or directory: '%s'", name);

	dot[1] = 'o';
	if ((casm->obj = fopen(name, "w")) == NULL)
		return error("Failed to create object file: '%s'", name);

	dot[0] = 's';
	casm->name = name;
	casm->col = casm->row = 0;
	casm->idx = casm->len = 0;
	casm->buf[BUF_SIZE - 1] = '\0';

	return 0;
}
