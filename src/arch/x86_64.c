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

#include "../ast.h"
#include "../casm.h"

static const char *operators[] = {
	/* TODO: fill x86_64 operator strings */
	NULL
};

static const char *registers[] = {
	/* TODO: fill x86_64 register strings */
	NULL
};

int
assemble(FILE *file, char *name)
{
	struct lexer lex;
	struct node *ast;

	lex = lexer_new(file);
	ast = ast_new(operators, registers, &lex);

	/* TODO: check syntax error and generate object code */

	lexer_free(&lex);

	return 0;
}
