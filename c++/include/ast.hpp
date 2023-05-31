#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <list>
#include "token.hpp"
#include "lexer.hpp"

struct AstNode {
	Token token;
	AstNode *left;
	AstNode *right;
	bool brace;

	AstNode();
	AstNode(Token _token, AstNode *_left, AstNode *_right, bool _brace);
	~AstNode();

	void log(int depth);
	string to_string();
};

struct AstTree {
	AstNode *root;
	Lexer lexer;

	AstTree(Lexer &lex);
	~AstTree();

	list<AstNode *> getNodeList(TokenList &tokens);
	AstNode *parseToken(list<AstNode *> nodeList);
};

#endif