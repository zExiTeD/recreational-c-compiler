#ifndef LEXER_H
#define LEXER_H

const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary"
};

const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);


typedef enum {
    EOF,
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


#endif//LEXER_H
