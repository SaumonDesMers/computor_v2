#include <iostream>
#include <vector>

using namespace std;

struct Token;
typedef vector<Token> TokenList;

void panic(string msg) {
	cerr << msg << endl;
	exit(1);
}

enum TokenType {
	PLUS,
	MINUS,
	MULT,
	DIV,
	MOD,
	NUMBER,
	LPAR,
	RPAR,
	LHOOK,
	RHOOK,
	COMMA,
	SEMICOLON,
	EQUAL,
	QUESTION,
	VAR,
	I,
	MATMULT,
	POWER,
	SUBTREE,
	NONE,
};

string tokenTypeToStr(TokenType type) {
	string tab[] = { "PLUS", "MINUS", "MULT", "DIV", "MOD", "NUMBER", "LPAR", "RPAR", "LHOOK", "RHOOK", "COMMA", "SEMICOLON", "EQUAL", "QUESTION", "VAR", "I", "MATMULT", "POWER", "SUBTREE", "NONE", };
	return tab[int(type)];
}

struct Token {
	TokenType type;
	string raw;

	Token(): type(NONE), raw("") {}
	Token(char _c, TokenType _type): type(_type), raw(string(1, _c)) {}
	Token(string _str, TokenType _type): type(_type), raw(_str) {}
};

struct SubTree: public Token {
	TokenList tokens;

	SubTree(TokenList::iterator it, TokenList::iterator ite): Token("", SUBTREE) {
		tokens.assign(it, ite);
	}
};

struct Lexer {
	TokenList tokens;

	Lexer(string str) {
		for (size_t i=0; i < str.size(); i++) {
			
			if (isspace(str[i]))
				continue;
			
			if (str[i] == '+')
				tokens.push_back(Token(str[i], PLUS));
			else if (str[i] == '-')
				tokens.push_back(Token(str[i], MINUS));
			else if (str[i] == '*')
				tokens.push_back(Token(str[i], MULT));
			else if (str[i] == '/')
				tokens.push_back(Token(str[i], DIV));
			else if (isdigit(str[i]))
				tokens.push_back(Token(str[i], NUMBER));
			else
				panic("Unexpected syntax: '" + string(1, str[i]) + "'");
		}
	}
};

struct AstNode {
	Token token;
	AstNode *left;
	AstNode *right;

	AstNode(Token _token, AstNode *_left, AstNode *_right): token(_token), left(_left), right(_right) {}
};

struct AstTree {
	AstNode *root;

	AstTree(Lexer &lex) {

	}
};


void log(TokenList list) {
	for (auto &t: list) {
		cout << t.raw << ": " << tokenTypeToStr(t.type) << endl;
	}
}



int main() {
	
	Lexer lex("1 + (2 - 6) * 8 / 5");

	// 1 + (2 + 6) * 8 / 5
	
	// 1 + st1 * 8 / 5
	// st1 = 2 + 6

	// 1 + st2
	// st1 = 2 + 6
	// st2 = st1 * 8 / 5

	SubTree st(lex.tokens.begin()+2, lex.tokens.begin()+5);
	

	log(lex.tokens);
	cout << endl;
	log(st.tokens);
	return 0;
}