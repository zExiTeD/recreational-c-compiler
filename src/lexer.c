#include "../include/lexer.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary"
};

const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

Lexer Lexer_Init(FILE* file_d) {
	Lexer lexer;

	fseek(file_d, 0, SEEK_END);
	uint32_t file_size = ftell(file_d);
	printf("size of file := %d \n", file_size);
	
	fseek(file_d, 0, SEEK_SET);
	
	lexer.input = (char *)malloc(file_size +1);
	if (!lexer.input) {
		exit(-1);
	}

	fread(lexer.input , 1  ,file_size,file_d);
	lexer.input[file_size] = '\0';
	fclose(file_d);

	printf("data :\n %s",lexer.input);

	return lexer;
}

void Lexer_Tokenize(Lexer *lexer){
	uint32_t index = 0;
	char buffer[1024];
	while( lexer->input[index] != '\0'){
		if ( isalpha(lexer->input[index]) ) {
			uint32_t len = index;
			while(!isspace(lexer->input[len])){
				len ++;
			}
			strncpy(buffer,lexer->input + index,(len - index));
			buffer[len - index ] = '\0';
			printf("IDENTIFIER: %s\n", buffer);
			index =index + len;
		}
		index ++;
	}
}

const char* 
token_type_to_string(TokenType type) {
    switch (type) {
        case EOF_TOKEN: return "EOF";
        case IDENTIFIER: return "IDENTIFIER";
        case NUMBER: return "NUMBER";
        case STRING: return "STRING";
        case CHAR: return "CHAR";
        case KEYWORD: return "KEYWORD";
        case OPERATOR: return "OPERATOR";
        case PUNCTUATION: return "PUNCTUATION";
        case COMMENT: return "COMMENT";
        case WHITESPACE: return "WHITESPACE";
        case UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}
