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
#define TOKEN_SIZE 64

#include <stdio.h>

struct file {
	char *name;
	FILE *file;
};

/* main.c */
struct file file_open(char *);

/* arch/x86-64.c */
int codegen(struct file *);

/* utils.c */
int usage(void);
int error(const char *, ...);

#endif
