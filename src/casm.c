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
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static const char *name; /* name of this program */

static void
crash(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);

	exit(EXIT_FAILURE);
}

struct casm
casm_new(char *file)
{
	struct casm casm;
	char *dot;

	casm.name = file;

	if ((dot = strrchr(casm.name, '.')) == NULL)
		crash("%s: No file extension: '%s'\n", name, file);
	if (strchr(dot, 's') == NULL)
		crash("%s: Invalid extension: '%s'\n", name, file);
	if ((casm.asm = fopen(casm.name, "r")) == NULL)
		crash("%s: No such file: '%s'\n", name, file);

	dot[1] = 'o';

	if ((casm.obj = fopen(casm.name, "w")) == NULL)
		crash("%s: Failed to create file: '%s'\n", name, file);

	dot[1] = 's';

	return casm;
}

void
casm_free(struct casm *casm)
{
	fclose(casm->asm);
	fclose(casm->obj);
}

int
main(int argc, char *argv[])
{
	struct casm casm;
	int stat;

	name = argv[0];
	stat = EXIT_SUCCESS;

	if (argc == 1)
		crash("usage: %s file...\n", name);

	for (++argv, --argc; argc; ++argv, --argc) {
		casm = casm_new(*argv);
		stat |= casm_assemble(&casm);
		casm_free(&casm);
	}

	return stat;
}
