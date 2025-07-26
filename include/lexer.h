#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

typedef enum {
    EOF_TOKEN,
    IDENTIFIER,
    NUMBER,
    STRING,
    CHAR,
    KEYWORD,
    OPERATOR,
    PUNCTUATION,
		COMMENT,
		PP_DIRECTIVE,
		UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char *data;
    int line;
} Token;

typedef struct {
	Token *tokens;
	char 	*input;
	int token_index;
}Lexer;

extern const char* keywords[];
extern const int num_keywords;

Lexer* Lexer_Init(FILE* file);
void	Lexer_Tokenize(Lexer* lexer);
int	check_is_keyword(char data[]);

Token get_next_token(FILE* file);                     
const char* token_type_to_string(TokenType type);
#endif//LEXER_H
