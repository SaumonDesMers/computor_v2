#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <list>
#include "token.hpp"
#include "lexer.hpp"

struct Node {
	Token token;
	Node *left;
	Node *right;
	bool brace;

	Node();
	Node(Token _token, Node *_left, Node *_right, bool _brace);
	~Node();

	void log(int depth);
	string to_string();
};

struct Ast {
	Node *root;
	Lexer lexer;

	Ast(Lexer &lex);
	~Ast();

	list<Node *> getNodeList(TokenList &tokens);
	Node *parseToken(list<Node *> nodeList);
};

#endif