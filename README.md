C-like Assembler
================

An assembler that easily work together with C.

Features
--------

**Functional Features:**

* It supports C-like syntax and function.
* It could define function in C header file.

**Non-Functional Features:**

* It generates ELF object file.
* It works on Unix-like systems.

**Supported CPUs:**

* x86-64

Design
------

CASM uses Intel-style syntax which places destination register before sources.

`opcode dest src1, src2;`

For instance, assigning zero in register `rax` would look like:

`mov rax, 0;`

Usage
-----

The assembly language can be linked with C like below.

**Header file (`add.h`)**

```c
int add(int, int);
```

**Assembly code (`add.s`)**

```as
#include "add.h"

/* assembly function to add two integers */
int
add(int x, int y)
{
	mov eax, x; /* load x into eax */
	add eax, y; /* add y to eax */

	return;     /* return value is in eax */
}
```

**C code (`main.c`)**

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

1. **Assemble the `add.s`**

```sh
casm add.s
```

2. **Compile the `main.c`**

```sh
cc -c main.c
```

3. **Link them into one executable**

```sh
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
