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

#include <stdio.h>

struct casm {
	const char *name;
	FILE *src, *obj;
};

int casm_init(struct casm *, const char *); /* init.c */
int casm_codegen(struct casm *);            /* x86-64.c */
void casm_free(struct casm *);              /* free.c */

/* utils.c */
int usage(void);
int error(const char *, ...);

#endif
