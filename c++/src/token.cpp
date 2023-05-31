#include "token.hpp"

using namespace std;

string tokenTypeToStr(TokenType type) {
	string str = "";
	switch (type) {
		case OPERATOR: str = "OPERATOR"; break;
		case PLUS: str = "PLUS"; break;
		case MINUS: str = "MINUS"; break;
		case MULT: str = "MULT"; break;
		case DIV: str = "DIV"; break;
		case MOD: str = "MOD"; break;
		case POWER: str = "POWER"; break;
		case MATMULT: str = "MATMULT"; break;
		case OPERAND: str = "OPERAND"; break;
		case I: str = "I"; break;
		case VAR: str = "VAR"; break;
		case NUMBER: str = "NUMBER"; break;
		case BRACE: str = "BRACE"; break;
		case LBRACE: str = "LBRACE"; break;
		case RBRACE: str = "RBRACE"; break;
		case LHOOK: str = "LHOOK"; break;
		case RHOOK: str = "RHOOK"; break;
		case COMMA: str = "COMMA"; break;
		case SEMICOLON: str = "SEMICOLON"; break;
		case EQUAL: str = "EQUAL"; break;
		case QUESTION: str = "QUESTION"; break;
		case SUBTREE: str = "SUBTREE"; break;
		case NONE: str = "NONE"; break;
	}
	return str;
}

// class Token
Token::Token(): type(NONE), raw("") {}
Token::Token(char _c, int _index, TokenType _type): type(_type), raw(string(1, _c)), index(_index) {}
Token::Token(string _str, int _index, TokenType _type): type(_type), raw(_str), index(_index) {}

void log(TokenList list) {
	for (auto &t: list) {
		cout << t.raw << ": " << tokenTypeToStr(t.type) << endl;
	}
}