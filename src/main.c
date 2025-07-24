#include <stdio.h>
#include "../include/lexer.h"

int 
main(int argc,char* argv[]) {
	FILE *filed = fopen("test/test.c","r");
	if (filed == NULL) {
		printf( "couldnt open file \n");
		return -1;
	}

 Token token; //keep reading tokens until we hit the end of the file
    do {
        token = get_next_token(filed);  //call the lexer
        printf("Token: %-12s Lexeme: %s\n", 
               token_type_to_string(token.type),  //converting to string
               token.lexeme);                     //print the actual text(ex "int","main","{" )
    } while (token.type != EOF_TOKEN);  //stop when eof token is reached
    fclose(filed);
    return 0;
}
