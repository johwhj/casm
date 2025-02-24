C-like Assembler
================

An assembler that easily work together with C.

Features
--------

**Functional Features:**

- Support C header file parsing.
- Support C function definition.
- Support ELF file format.
- Support x86-64 System V AMD64 ABI.

**Non-functional Features:**

- Written in standard C89(ISO/IEC 9899:1990).

Design
------

CASM is created to make it easy for programmers to use a familiar C-like style
when writing assembly code. This helps them define and call functions in a way
that feels similar to C programming. CASM can read C header files, which allows
users to declare functions that can be used in C code.

For example, consider a simple header file `add.h` that declares a function for
adding two integers:

```c
int add(int, int);
```

In the assembly code `add.s`, the function is defined using a C-like syntax,
where the setup for the stack is handled automatically:

```asm
#include "add.h"

int
add(int x, int y)
{
	mov eax, x;  /* Move the first argument into eax */
	add eax, y;  /* Add the second argument to eax */

	ret;         /* Return to where the function is called */
}
```

This design allows programmers to write assembly code that is clear and
organized, similar to higher-level programming languages.

In the C code `main.c`, the `add` function can be called just like  any other C
function:

```c
#include "add.h"
#include <stdio.h>

int
main(void)
{
	int x, y, z;

	x = 10;
	y = 15;
	z = add(x, y);

	printf("%d\n", z);

	return 0;
}
```

By handling stack setup automatically and offering a simple way to define
functions, CASM helps programmers work more efficiently and makes it easier for
those who are new to assembly language. This ensures that developers can write
effective assembly code while maintaining clarity and organization.

Usage
-----

To create the executable program with above example, use these commands.

```sh
casm add.s
cc -c main.c
cc -o add add.o main.o
```

Installation
------------

To install this assembler, follow the below steps.

1. **Clone this repository:**

```sh
git clone https://codeberg.org/johwhj/casm.git
```

2. **Go to the project directory:**

```sh
cd casm
```

3. **Build:**

```sh
make x86-64
```

4. **Install:** (You might need root privileges)

```sh
make install
```

License
-------

casm by Woohyun Joh is marked with CC0 1.0.
