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

Lexer* Lexer_Init(FILE* file_d) {
	Lexer* lexer = (Lexer*) malloc(sizeof(Lexer));

	fseek(file_d, 0, SEEK_END);
	uint32_t file_size = ftell(file_d);
	printf("size of file := %d \n", file_size);
	
	fseek(file_d, 0, SEEK_SET);
	
	lexer->input = (char *)malloc(file_size +1);
	if (!lexer->input) {
		printf("error : Lexer_Init(); lexer.input\n");
		exit(-1);
	}

	fread(lexer->input , 1  ,file_size,file_d);
	lexer->input[file_size] = '\0';
	fclose(file_d);

	printf("data :\n%s",lexer->input);
	
	lexer->tokens = (Token *)malloc(1024 * sizeof(Token)); 
	if (!lexer->tokens) {
		printf("error : Lexer_Init(); lexer.tokens\n");
		exit(-1);
	}

	return lexer;
}

void Lexer_Tokenize(Lexer *lexer){
	uint32_t index = 0;
	char buffer[1024];
	while( lexer->input[index] != '\0'){

		if (isspace(lexer->input[index])) {
			index++;
			continue;
		}

		if ( isalpha(lexer->input[index]) ) {
			uint32_t len = 0;
			while (lexer->input[index + len] != '\0' &&
					!isspace(lexer->input[index + len]) &&
					isalpha(lexer->input[index + len])) {
				len++;
			}

			strncpy(buffer,lexer->input + index,len);
			buffer[len ] = '\0';
			index = index + len;
			printf("IDENTIFIER: %s\n", buffer);
		}

		if (ispunct(lexer->input[index])) {
			printf("SYMBOL: %c\n", lexer->input[index]);
			index++;
			continue;
		}
			
		if (isdigit(lexer->input[index])) {
			uint32_t len = 0;
			while (isdigit(lexer->input[index + len])) len++;
			strncpy(buffer, lexer->input + index, len);
			buffer[len] = '\0';
			printf("NUMBER: %s\n", buffer);
			index += len;
			continue;
		}	
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
