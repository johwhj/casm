include config.mk

SRC = src/ast.c src/casm.c src/lexer.c src/utils.c src/arch/$(ARCH).c
OBJ = $(notdir $(SRC:.c=.o))

all: casm

casm:
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) -o casm $(OBJ)

clean:
	rm -f casm a.out test_* $(OBJ)

check: casm
	$(CC) $(CFLAGS) -o test_lexer lexer.o test/lexer.c
	./test_lexer

dist: clean
	mkdir -p casm-$(VERSION)
	cp -r LICENSE Makefile README.md config.mk src/ casm-$(VERSION)
	tar -cf - casm-$(VERSION) | xz > casm-$(VERSION).tar.xz
	rm -rf casm-$(VERSION)

install: casm
	mkdir -p $(PREFIX)/bin
	cp -f casm $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/casm

uninstall:
	rm -f $(PREFIX)/bin/casm

.PHONY: all casm clean check dist install uninstall
