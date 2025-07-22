all : compiler

compiler: src/main.c
	gcc src/main.c -o build/bin/compiler
