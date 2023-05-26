#include <iostream>
#include <vector>
#include "error.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "ast.hpp"

using namespace std;

int main(int ac, char *av[]) {

	if (ac != 2) {
		panic("Wrong argument.");
	}
	
	Lexer lex(av[1]);
	log(lex.tokens);

	AstTree ast(lex);

	return 0;
}