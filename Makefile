include config.mk

CC = c89
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all: help

help:
	@echo "usage: make help"
	@echo "       make x86-64"
	@echo "       make clean"
	@echo "       make install"
	@echo "       make uninstall"

x86-64:
	$(CC) $(CFLAGS) -c src/casm.c src/$@.c src/lex.c
	$(CC) -o casm casm.o $@.o

clean:
	rm -f casm casm.o *.o
