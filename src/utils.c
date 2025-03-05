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

void
usage(void)
{
	(void)fprintf(stderr, "usage: "PROGNAME" file...\n");

	exit(EXIT_FAILURE);
}

int
error(const char *fmt, ...)
{
	va_list ap;

	(void)fprintf(stderr, PROGNAME": ");

	va_start(ap, fmt);
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);

	(void)fputc('\n', stderr);

	return 1;
}
