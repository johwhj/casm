C-like Assembler
================

An assembler that easily work together with C.

Features
--------

**Functional Features:**

- Support C header file parsing.
- Support C-like function definition and call.
- Support ELF file format.
- Support x86-64.

**Non-functional Features:**

- Written in standard C89.

Design
------

CASM is designed to help programmers use familiar C-like syntax when writing
assembly language. It allows programmers to define functions, so they can
organize their code into reusable parts. They can also define functions that are
declared in C header files, making it easy to call these functions from C code.

Usage
-----

**Header file (`add.h`)**

This header file declares a function that returns addition of two integers.

```c
int add(int, int);
```

**Assembly code (`add.s`)**

In this assembly code, the function is defined using a C-like syntax. The setup
for the stack is done automatically.

```asm
#include "add.h"

int
add(int x, int y)
{
	mov eax, x;
	add eax, y;

	return;
}
```

**C code (`main.c`)**

In this C code, the `add` function can be called just like any other C function.

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

**Compile and link**

To create the executable program, use these commands.

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

3. **Install:** (You might need root privileges)

```sh
make install
```

License
-------

dslibc by Woohyun Joh is marked with CC0 1.0.
