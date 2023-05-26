#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include "token.hpp"
#include "lexer.hpp"

struct AstNode {
	Token token;
	AstNode *left;
	AstNode *right;

	AstNode(Token _token, AstNode *_left, AstNode *_right);
};

struct AstTree {
	AstNode *root;

	AstTree(Lexer &lex);

	void separateParenthesis(TokenList &tokens);
};

#endif