C-like Assembler (CASM)
=======================

CASM is an assembler that works well with C.

Features
--------

**Functional:**

- Parses C header files.
- Supports C function definitions.
- Allows C-like global variable declarations and initializations.
- Uses ELF file format.
- Follows x86-64 System V AMD64 ABI.

**Non-functional:**

- Written in standard C89.
- Works on Unix-like systems.

Design
------

CASM lets programmers write assembly code in a C-like style, making it easier
to define and call functions. It can read C header files for function
definitions.

Example header file `add.h`:

```c
int add(int, int);
```

Assembly code `add.s`:

```asm
#include "add.h"

int
add(int x, int y)
{
	mov eax, x;
	add eax, y;
	ret;
}
```

C code `main.c`:

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

Usage
-----

To create the executable, use:

```sh
casm add.s
cc -c main.c
cc -o add add.o main.o
```

Installation
------------

1. **Clone the repository:**

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

4. **Install:** (may need root access)

```sh
make install
```

License
-------

casm by Woohyun Joh is marked with CC0 1.0.
