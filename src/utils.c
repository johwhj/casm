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

int
usage
{
	fprintf(stderr, "usage: "PROGNAME" file...\n");

	return 1;
}

int
error(const char *fmt, ...)
{
	va_list ap;

	fprintf(stderr, PROGNAME": ");

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	fputc('\n', stderr);

	return 1;
}
