#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <vector>

using namespace std;

enum TokenType {
	PLUS, // +
	MINUS, // -
	MULT, // *
	DIV, // /
	MOD, // %
	LPAR, // (
	RPAR, // )
	LHOOK, // [
	RHOOK, // ]
	COMMA, // ,
	SEMICOLON, // ;
	EQUAL, // =
	QUESTION, // ?
	POWER, // ^
	MATMULT, // **
	I, // i
	VAR, // [0-9].
	NUMBER, // [a-zA-Z]
	SUBTREE,
	NONE,
};

string tokenTypeToStr(TokenType type);

struct Token;
typedef vector<Token> TokenList;

struct Token {
	TokenType type;
	string raw;

	TokenList tokens;

	Token();
	Token(char _c, TokenType _type);
	Token(string _str, TokenType _type);

	Token(TokenList::iterator it, TokenList::iterator ite, string _raw);
	Token(TokenList const &tokens, string _raw);
};


// struct SubTree: public Token {
// 	TokenList tokens;

// 	SubTree(TokenList::iterator it, TokenList::iterator ite, string raw);
// 	SubTree(TokenList const &tokens, string raw);
// };

void log(TokenList list);

#endif