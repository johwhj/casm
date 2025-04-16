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
	/* 64-bit general-purpose */
	"rax", "rbx", "rcx", "rdx", "rsi", "rdi", "rbp", "rsp",
	"r8",  "r9",  "r10", "r11", "r12", "r13", "r14", "r15",

	/* 32-bit general-purpose */
	"eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp",
	"r8d", "r9d", "r10d","r11d","r12d","r13d","r14d","r15d",

	/* 16-bit general-purpose */
	"ax",  "bx",  "cx",  "dx",  "si",  "di",  "bp",  "sp",
	"r8w", "r9w", "r10w","r11w","r12w","r13w","r14w","r15w",

	/* 8-bit low general-purpose */
	"al",  "bl",  "cl",  "dl",  "sil", "dil", "bpl", "spl",
	"r8b", "r9b", "r10b","r11b","r12b","r13b","r14b","r15b",

	/* 8-bit high general-purpose */
	"ah", "bh", "ch", "dh",

	/* Instruction pointer and flags */
	"rip", "rflags",

	/* Segment registers */
	"cs", "ds", "es", "fs", "gs", "ss",

	/* Control registers */
	"cr0", "cr2", "cr3", "cr4", "cr8",

	/* Debug registers */
	"dr0", "dr1", "dr2", "dr3", "dr6", "dr7",

	/* Descriptor table registers */
	"gdtr", "ldtr", "idtr", "tr",

	/* End of array */
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
