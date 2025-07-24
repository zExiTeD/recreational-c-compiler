#include "../include/lexer.h"
#include <string.h>
const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary"
};

const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

Token 
get_next_token(FILE* file) {
    Token t;
    t.type = EOF_TOKEN;
    snprintf(t.lexeme, sizeof(t.lexeme), "EOF");
    t.line = 1;
    return t;
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
