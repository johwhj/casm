include config.mk

all: help

help:
	@echo "usage: make help"
	@echo "       make x86-64"
	@echo "       make clean"
	@echo "       make install"
	@echo "       make uninstall"

x86-64:
	$(CC) $(CFLAGS) -c src/casm.c src/$@.c
	$(CC) -o casm casm.o

clean:
	rm -f casm casm.o *.o

dist: clean
	mkdir -p casm-$(VERSION)

install:
	mkdir -p $(PREFIX)/bin
	cp -f casm $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/casm
