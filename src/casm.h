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
#define BUF_SIZE 4096

#include <stdio.h>

struct casm {
	FILE *src, *obj;
	long col, row;
	size_t idx, len;
	char buf[BUF_SIZE]; /* contains \0 at BUF_SIZE - 1 */
	const char *name;
};

int casm_init(struct casm *, const char *); /* init.c */
int casm_codegen(struct casm *);            /* x86-64.c */
char *casm_token(struct casm *);            /* token.c */
void casm_free(struct casm *);              /* free.c */

/* utils.c */
void usage(void);
int error(const char *, ...);

#endif
