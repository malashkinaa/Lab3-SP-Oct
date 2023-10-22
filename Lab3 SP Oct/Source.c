#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TYPE_SIZE 20
#define MAX_VALUE_SIZE 50

// Structure for representing lexemes
struct Lexeme {
	char type[MAX_TYPE_SIZE];
	char value[MAX_VALUE_SIZE];
};

// Structure for representing the lexeme table
struct LexemeTable {
	struct Lexeme* lexemes;
	int size;
};

// Initialize the lexeme table
struct LexemeTable initLexemeTable() {
	struct LexemeTable table;
	table.lexemes = NULL;
	table.size = 0;
	return table;
}

// Add a lexeme to the table
void addLexeme(struct LexemeTable* table, const char* type, const char* value) {
	table->size++;
	table->lexemes = (struct Lexeme*)realloc(table->lexemes, table->size * sizeof(struct Lexeme));
	strcpy_s(table->lexemes[table->size - 1].type, MAX_TYPE_SIZE, type);
	strcpy_s(table->lexemes[table->size - 1].value, MAX_VALUE_SIZE, value);
}

// Determine the type of a lexeme
const char* getLexemeType(const char* lexemeValue) {
	if (isdigit(lexemeValue[0]) || (lexemeValue[0] == '-' && isdigit(lexemeValue[1]))) {
		return "Number";
	}
	else if (strcmp(lexemeValue, "if") == 0 || strcmp(lexemeValue, "else") == 0) {
		return "Keyword";
	}
	else if (strcmp(lexemeValue, "{") == 0 || strcmp(lexemeValue, "}") == 0 ||
		strcmp(lexemeValue, "(") == 0 || strcmp(lexemeValue, ")") == 0 ||
		strcmp(lexemeValue, "+") == 0 || strcmp(lexemeValue, "-") == 0) {
		return "Operator";
	}
	else {
		return "Identifier";
	}
}

// Lexical analyzer for identifiers
void analyzeIdentifiers(const char* code, struct LexemeTable* table) {
	char identifier[MAX_VALUE_SIZE];
	int i = 0;

	while (code[i] != '\0') {
		if (isalpha(code[i]) || code[i] == '_') {
			int j = 0;
			while (isalnum(code[i]) || code[i] == '_') {
				identifier[j++] = code[i++];
			}
			identifier[j] = '\0';

			const char* type = getLexemeType(identifier);
			addLexeme(table, type, identifier);
		}
		else if (code[i] == ' ' || code[i] == '\t' || code[i] == '\n') {
			i++;
		}
		else {
			char symbol[2];
			symbol[0] = code[i];
			symbol[1] = '\0';
			const char* type = getLexemeType(symbol);
			addLexeme(table, type, symbol);
			i++;
		}
	}
}

// Main function for code analysis
struct LexemeTable analyze(const char* code) {
	struct LexemeTable table = initLexemeTable();

	analyzeIdentifiers(code, &table);

	return table;
}

int main() {
	const char* code = "int main() { if (x > 0) y = x + 1; else y = x - 1; }";
	struct LexemeTable lexemeTable = analyze(code);

	// Output the analysis results with lexeme types
	for (int i = 0; i < lexemeTable.size; i++) {
		printf("Lexeme: %s, Type: %s\n", lexemeTable.lexemes[i].value, lexemeTable.lexemes[i].type);
	}

	// Free memory allocated for the lexeme table
	free(lexemeTable.lexemes);

	return 0;
}
