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
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int
assemble(const char *name, char *file)
{
	FILE *asm, *obj;
	char *dot;

	if ((dot = strrchr(file, '.')) == NULL)
		return error("%s: No file extension: %s\n", name, file);
	if (strcmp(dot, ".s"))
		return error("%s: Invalid file extension: %s\n", name, file);
	if ((asm = fopen(file, "r")) == NULL)
		return error("%s: No such file: %s\n", name, file);

	dot[1] = 'o';

	if ((obj = fopen(file, "w")) == NULL)
		return error("%s: Failed to create file: %s\n", name, file);

	dot[1] = 's';

	return generate(asm, obj, file);
}

int
main(int argc, char *argv[])
{
	const char *name; /* name of this program */
	int stat;         /* EXIT_SUCCESS or EXIT_FAILURE */

	name = argv[0];
	stat = EXIT_SUCCESS;

	if (argc == 1)
		return error("usage: %s file...\n", name);
	for (++argv, --argc; argc; ++argv, --argc)
		stat |= assemble(name, *argv);

	return stat;
}
