#include "../include/lexer.h"

const char* keywords[] = {
	"auto", "break", "case", "char", "const", "continue", "default", "do",
	"double", "else", "enum", "extern", "float", "for", "goto", "if",
	"inline", "int", "long", "register", "restrict", "return", "short",
	"signed", "sizeof", "static", "struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary"
};

const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

Lexer* 
Lexer_Init(FILE* file_d) {
	Lexer* lexer = (Lexer*) malloc(sizeof(Lexer));
	lexer-> token_index = 0;

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

void 
Lexer_Tokenize(Lexer *lexer){
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

			lexer->tokens[lexer->token_index].data.str = malloc(sizeof(char) * (len+1));
			strcpy(lexer->tokens[lexer->token_index].data.str, buffer);

			if(check_is_keyword(buffer)) {
				lexer->tokens[lexer->token_index].type = KEYWORD;
				printf("KEYWORD: %s\n", buffer);
			} else {
				lexer->tokens[lexer->token_index].type = IDENTIFIER;
				printf("IDENTIFIER: %s\n", buffer);
			}
			lexer->token_index +=1;

		}

		if (ispunct(lexer->input[index])) {
			switch(lexer->input[index]) {
				case '"' : 
					{
						uint32_t len = 1;         

						while (lexer->input[index + len] != '\0' && lexer->input[index + len] != '"') {
							len++;
						}

						if (lexer->input[index + len] == '"') {
							len++;      
						} else {
							printf("Error: Unterminated string literal\n");
							break;
						}

						if (len >= sizeof(buffer)) {
							printf("Error: String too long\n");
							break;
						}

						strncpy(buffer, lexer->input + index, len);
						buffer[len] = '\0';

						lexer->tokens[lexer->token_index].data.str = malloc(sizeof(char) * (len + 1));
						if (!lexer->tokens[lexer->token_index].data.str) {
							printf("Error: Memory allocation failed\n");
							break;
						}
						strcpy(lexer->tokens[lexer->token_index].data.str, buffer);
						lexer->tokens[lexer->token_index].type = STRING;
						lexer->token_index += 1;  						
						index += len;

						printf("STRING: %s\n", buffer);
					}break;
				default : 
					{
						if (index + 1 < strlen(lexer->input) && ispunct(lexer->input[index + 1])) {
							char two_char[3];
							two_char[0] = lexer->input[index];
							two_char[1] = lexer->input[index + 1];
							two_char[2] = '\0';

							lexer->tokens[lexer->token_index].data.ch[0] = lexer->input[index];
							lexer->tokens[lexer->token_index].data.ch[1] = lexer->input[index + 1];
							lexer->tokens[lexer->token_index].data.ch[2] = '\0';
							lexer->tokens[lexer->token_index].type = OPERATOR;
							lexer->token_index += 1;
							index += 2; // Skip both characters

							printf("OPERATOR: %s\n", two_char);
						} else {
							lexer->tokens[lexer->token_index].data.ch[0] = lexer->input[index];
							lexer->tokens[lexer->token_index].data.ch[1] = '\0';
							lexer->tokens[lexer->token_index].type = OPERATOR;
							lexer->token_index += 1;
							index += 1;

							printf("OPERATOR: %c\n", lexer->input[index - 1]);

						}break;
					}
					index++;
					continue;
			}
		}

		if (isdigit(lexer->input[index])) {
			uint32_t len = 0;
			while (isdigit(lexer->input[index + len])) len++;

			strncpy(buffer, lexer->input + index, len);
			buffer[len] = '\0';


			lexer->tokens[lexer->token_index].data.str = malloc(sizeof(char) * (len + 1));
			if (!lexer->tokens[lexer->token_index].data.str) {
				printf("Error: Memory allocation failed\n");
				break;
			}
			strcpy(lexer->tokens[lexer->token_index].data.str, buffer);

			lexer->tokens[lexer->token_index].type = NUMBER;
			lexer->token_index += 1;

			printf("NUMBER: %s\n", buffer);
			index += len;;
		}	
	}
}

int
check_is_keyword(char* data) {
	for (size_t i = 0; i < num_keywords; i++) {
		if (strcmp(data, keywords[i]) == 0)
			return 1;
	}
	return 0;
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
		case UNKNOWN: return "UNKNOWN";
		default: return "UNKNOWN";
	}
}
