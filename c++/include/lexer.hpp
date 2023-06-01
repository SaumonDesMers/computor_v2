#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include "token.hpp"

using namespace std;

struct Lexer {
	string input;
	TokenList tokens;

	Lexer(string const &str);

	void detectBasicToken(string const &str);

};

#endif