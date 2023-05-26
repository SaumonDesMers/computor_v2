#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include "token.hpp"

using namespace std;

struct Lexer {
	TokenList tokens;

	Lexer(string const &str);

	void detectToken(string const &str);

};

#endif