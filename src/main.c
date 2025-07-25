#include <stdio.h>
#include "../include/lexer.h"
#include <stdlib.h>

int 
main(int argc,char* argv[]) {
	FILE *file_d = fopen("test/test.c","r");
	if (file_d == NULL) {
		printf( "couldnt open file \n");
		return -1;
	}

	Lexer* lexer = Lexer_Init( file_d);

	Lexer_Tokenize( lexer);

	free(lexer);
	return 0;
}
