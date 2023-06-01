#include "lexer.hpp"
#include "error.hpp"

Lexer::Lexer(string const &str): input(str) {
	this->detectBasicToken(str);
}

static TokenType basicCharToTokenType(char c) {
	switch (c) {
		case '+': return PLUS;
		case '-': return MINUS;
		case '*': return MULT;
		case '/': return DIV;
		case '%': return MOD;
		case '(': return LBRACE;
		case ')': return RBRACE;
		case '[': return LHOOK;
		case ']': return RHOOK;
		case ',': return COMMA;
		case ';': return SEMICOLON;
		case '=': return EQUAL;
		case '?': return QUESTION;
		case '^': return POWER;
	}
	return NONE;
}

void Lexer::detectBasicToken(string const &input) {
	for (size_t i=0; i < input.size(); i++) {

		// escape whitespace
		if (isspace(input[i]))
			continue;

		// detect number
		int j = 0;
		while (isdigit(input[i])) {
			if (isdigit(input[i+j]) || input[i+j] == '.')
				j++;
			else if (j > 0) {
				this->tokens.push_back(Token(input.substr(i, j), i, NUMBER));
				i += j-1;
				break;
			}
		}
		if (j > 0) continue;

		// detect variable/function name
		j = 0;
		while (isalpha(input[i])) {
			if (isalpha(input[i+j]))
				j++;
			else if (j > 0) {
				string raw = input.substr(i, j);
				this->tokens.push_back(Token(raw, i, raw == "i" ? I : VAR));
				i += j-1;
				break;
			}
		}
		if (j > 0) continue;

		// detect matrix multiplication
		if (input[i] == '*' && input[i+1] == '*') {
			this->tokens.push_back(Token("**", i, MATMULT));
			i++;
			continue;
		}

		// detect basic tokens
		TokenType type = basicCharToTokenType(input[i]);
		if (type != NONE) {
			this->tokens.push_back(Token(input[i], i, type));
			continue;
		}
		
		// error
		invalidSyntax(input, i);
	}
}