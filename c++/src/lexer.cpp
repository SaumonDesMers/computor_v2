#include "lexer.hpp"
#include "error.hpp"

Lexer::Lexer(string const &str) {
	this->detectToken(str);
}

void Lexer::detectToken(string const &str) {
	for (size_t i=0; i < str.size(); i++) {

		// escape whitespace
		if (isspace(str[i]))
			continue;

		// detect number
		int j = 0;
		while (isdigit(str[i])) {
			if (isdigit(str[i+j]) || str[i+j] == '.')
				j++;
			else if (j > 0) {
				tokens.push_back(Token(str.substr(i, j), NUMBER));
				i += j-1;
				break;
			}
		}
		if (j > 0) continue;

		// detect variable/function name
		j = 0;
		while (isalpha(str[i])) {
			if (isalpha(str[i+j]))
				j++;
			else if (j > 0) {
				string raw = str.substr(i, j);
				tokens.push_back(Token(raw, raw == "i" ? I : VAR));
				i += j-1;
				break;
			}
		}
		if (j > 0) continue;

		// detect matrix multiplication
		if (str[i] == '*' && str[i+1] == '*') {
			tokens.push_back(Token("**", MATMULT));
			i++;
			continue;
		}

		// detect basic tokens
		char basic_tokens[] = { '+', '-', '*', '/', '%', '(', ')', '[', ']', ',', ';', '=', '?', '^' };
		j = 0;
		while (j < 14) {
			if (str[i] == basic_tokens[j]) {
				tokens.push_back(Token(str[i], TokenType(j)));
				break;
			}
			j++;
		}
		if (j != 14) continue;
		
		// error
		panic(
			"Unexpected syntax:\n"
			+ str + "\n"
			+ string(i, ' ') + "\033[31m" + string(1, '^') + "\033[0m"
		);
	}
}