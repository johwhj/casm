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

int
main(int argc, char *argv[])
{
	struct casm casm;
	int state;

	state = 0;

	if (argc == 1)
		usage();
	for (--argc, ++argv; argc; --argc, ++argv) {
		state |= casm_init(&casm, *argv);
		state |= casm_codegen(&casm);

		casm_free(&casm);
	}

	return state;
}
