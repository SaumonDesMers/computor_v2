#include "token.hpp"

using namespace std;

string tokenTypeToStr(TokenType type) {
	string tab[] = { "PLUS", "MINUS", "MULT", "DIV", "MOD", "LPAR", "RPAR", "LHOOK", "RHOOK", "COMMA", "SEMICOLON", "EQUAL", "QUESTION", "POWER", "MATMULT", "I", "VAR", "NUMBER", "SUBTREE", "NONE" };
	return tab[int(type)];
}

// class Token
Token::Token(): type(NONE), raw("") {}
Token::Token(char _c, TokenType _type): type(_type), raw(string(1, _c)) {}
Token::Token(string _str, TokenType _type): type(_type), raw(_str) {}

Token::Token(TokenList::iterator it, TokenList::iterator ite, string _raw): type(SUBTREE), raw(_raw) {
	tokens.assign(it, ite);
}
Token::Token(TokenList const &_tokens, string _raw): type(SUBTREE), raw(_raw), tokens(_tokens) {}

void log(TokenList list) {
	for (auto &t: list) {
		cout << t.raw << ": " << tokenTypeToStr(t.type) << endl;
	}
}