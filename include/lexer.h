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
    WHITESPACE,
    UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[256];  //holds the actual token text (e.g., "int", "main")
    int line;          //line number for debugging
} Token;

extern const char* keywords[];
extern const int num_keywords;

Token get_next_token(FILE* file);                     
const char* token_type_to_string(TokenType type);  //SAME AS IN .C?
#endif//LEXER_H
