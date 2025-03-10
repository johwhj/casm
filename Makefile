include config.mk

SRC = src/main.c src/casm.c src/utils.c src/lexer.c
OBJ = *.o

all: help

help:
	@echo "usage: make help"
	@echo "       make x86-64"
	@echo "       make clean"
	@echo "       make install"
	@echo "       make uninstall"

x86-64:
	$(CC) $(CFLAGS) -c $(SRC) src/$@.c
	$(CC) -o casm $(OBJ)

clean:
	rm -f casm $(OBJ)

dist: clean
	mkdir -p casm-$(VERSION)
	cp -r LICENSE Makefile README.md config.mk src/ casm-$(VERSION)
	tar -cf - casm-$(VERSION) | xz > casm-$(VERSION).tar.xz
	rm -rf casm-$(VERSION)

install:
	mkdir -p $(PREFIX)/bin
	cp -f casm $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/casm

uninstall:
	rm -f $(PREFIX)/bin/casm
