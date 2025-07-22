all : compiler

build:
	mkdir -p build

build/bin:
	mkdir -p build/bin

build/main.o: src/main.c | build
	gcc -c src/main.c -o build/main.o

build/lexer.o: src/lexer.c | build
	gcc -c src/lexer.c -o build/lexer.o

compiler: build/main.o build/lexer.o | build/bin
	gcc build/main.o build/lexer.o -o build/bin/compiler

main: build/main.o

lexer: build/lexer.o

clean:
	rm -rf build

.PHONY: all main lexer compiler clean
