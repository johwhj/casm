# version
VERSION = 0.1.0

# path
PREFIX = /usr/local

# C compiler
CC = c89
CFLAGS = -Wall -Wextra -Wpedantic -Werror

# CPU architecture
ARCH = $(shell uname -m)
