#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ������
typedef enum {
	KEYWORD, IDENTIFIER, NUMBER, STRING, CHAR_CONST,
	PREPROCESSOR_DIRECTIVE, OPERATOR, PUNCTUATION, COMMENT, ERROR
} TokenType;

// ��������� ��� ������������� �������
typedef struct {
	char lexeme[100];
	TokenType type;
} Token;

// ������� ��� ���������� ���� �������
TokenType get_token_type(const char* lexeme) {
	// ����� ���������� ���� ������� ���
	// �������: �������� �� � ������� �������� ������
	if (strcmp(lexeme, "int") == 0 || strcmp(lexeme, "float") == 0) {
		return KEYWORD;
	}
	// ������� ���� �������� ��� ����� ���� ������
	// ...

	// ���� �� ������� ��������� ���, ��������� ERROR
	return ERROR;
}

// ������� ��� ������ ������� � ���������
void print_colored_token(Token token) {
	switch (token.type) {
	case KEYWORD:
		printf("\x1b[31m"); // �������� ���� ��� �������� ���
		break;
	case IDENTIFIER:
		printf("\x1b[32m"); // ������� ���� ��� ��������������
		break;
		// ������� ���� ������� ��� ����� ���� ������
		// ...
	default:
		break;
	}

	printf("< %s , %d >\x1b[0m\n", token.lexeme, token.type); // �������� �������
}

int main() {
	char program[1000];
	printf("Enter the program text:\n");
	fgets(program, sizeof(program), stdin);

	// ������������� strtok_s ��� �������� �� �������
	char* token = NULL;
	char* next_token = NULL;

	// ������� �������� �������� �� �������
	token = strtok_s(program, " \t\n", &next_token);
	while (token != NULL) {
		// ��������� ��� �������
		TokenType type = get_token_type(token);

		// ��������� ��������� �������
		Token current_token;
		strcpy_s(current_token.lexeme, sizeof(current_token.lexeme), token);
		current_token.type = type;

		// �������� ������� � ���������
		print_colored_token(current_token);

		// �������� �������� �������
		token = strtok_s(NULL, " \t\n", &next_token);
	}

	return 0;
}
