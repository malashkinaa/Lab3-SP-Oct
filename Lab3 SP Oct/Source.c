#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Типи лексем
typedef enum {
	KEYWORD, IDENTIFIER, NUMBER, STRING, CHAR_CONST,
	PREPROCESSOR_DIRECTIVE, OPERATOR, PUNCTUATION, COMMENT, ERROR
} TokenType;

// Структура для представлення лексеми
typedef struct {
	char lexeme[100];
	TokenType type;
} Token;

// Функція для визначення типу лексеми
TokenType get_token_type(const char* lexeme) {
	// Логіка визначення типу лексеми тут
	// Приклад: перевірка чи є лексема ключовим словом
	if (strcmp(lexeme, "int") == 0 || strcmp(lexeme, "float") == 0) {
		return KEYWORD;
	}
	// Додайте інші перевірки для інших типів лексем
	// ...

	// Якщо не вдалося визначити тип, повертаємо ERROR
	return ERROR;
}

// Функція для виводу лексеми з кольорами
void print_colored_token(Token token) {
	switch (token.type) {
	case KEYWORD:
		printf("\x1b[31m"); // Червоний колір для ключових слів
		break;
	case IDENTIFIER:
		printf("\x1b[32m"); // Зелений колір для ідентифікаторів
		break;
		// Додайте інші випадки для інших типів лексем
		// ...
	default:
		break;
	}

	printf("< %s , %d >\x1b[0m\n", token.lexeme, token.type); // Скидання кольорів
}

int main() {
	char program[1000];
	printf("Enter the program text:\n");
	fgets(program, sizeof(program), stdin);

	// Використовуємо strtok_s для розбиття на лексеми
	char* token = NULL;
	char* next_token = NULL;

	// Приклад розбиття програми на лексеми
	token = strtok_s(program, " \t\n", &next_token);
	while (token != NULL) {
		// Визначаємо тип лексеми
		TokenType type = get_token_type(token);

		// Створюємо структуру лексеми
		Token current_token;
		strcpy_s(current_token.lexeme, sizeof(current_token.lexeme), token);
		current_token.type = type;

		// Виводимо лексему з кольорами
		print_colored_token(current_token);

		// Отримуємо наступну лексему
		token = strtok_s(NULL, " \t\n", &next_token);
	}

	return 0;
}
