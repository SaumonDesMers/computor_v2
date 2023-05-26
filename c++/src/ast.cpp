#include <cstring>
#include <algorithm>
#include "ast.hpp"
#include "error.hpp"

// class AstNode
AstNode::AstNode(Token _token, AstNode *_left, AstNode *_right): token(_token), left(_left), right(_right) {}

// class AstTree
AstTree::AstTree(Lexer &lex) {
	vector<Token> tokens = lex.tokens;
	this->separateParenthesis(tokens);
}

void AstTree::separateParenthesis(TokenList &tokens) {
	vector<pair<Token, int>> tokenDepth;
	for (Token const &t: tokens)
		tokenDepth.push_back(make_pair(t, 0));

	int depth = 0;
	int maxDepth = 0;

	for (size_t i = 0; i < tokens.size(); i++) {
		if (tokens[i].type == LPAR) {
			depth++;
			maxDepth = max(maxDepth, depth);
		}
		tokenDepth[i].second = depth;
		if (tokens[i].type == RPAR)
			depth--;
	}

	for (auto &pair: tokenDepth)
		cout << pair.first.raw;
	cout << endl;
	for (auto &pair: tokenDepth)
		cout << char(pair.second == 0 ? ' ' : pair.second+48);
	cout << endl;

	int subTreeId = 0;

	// for each depth
	while (maxDepth > 0) {

		// for each set of same depth
		while (true) {
			auto it = find_if(tokenDepth.begin(), tokenDepth.end(), [maxDepth](pair<Token, int> &p) { return p.second == maxDepth; });
			auto ite = find_if(it, tokenDepth.end(), [maxDepth](pair<Token, int> &p) { return p.second != maxDepth; });

			if (it == tokenDepth.end()) {
				maxDepth--;
				break;
			}

			TokenList subTokenList;
			for (auto i = it; i < ite; i++)
				subTokenList.push_back(i->first);
			
			Token token(subTokenList, "st" + to_string(subTreeId++));

			cout << token.raw << ": ";
			for (auto iter = token.tokens.begin(); iter < token.tokens.end(); iter++)
				cout << iter->raw;
			cout << endl;

			auto pos = it - tokenDepth.begin()	;

			tokenDepth.erase(it, ite);

			tokenDepth.insert(tokenDepth.begin() + pos, make_pair(token, maxDepth-1));
		}
		
	}

}

// (7 + 3) * (10 / (12 / (3 + 1) - 1))
// 1     1   1     2     3     3    21

// st1 * (10 / (12 / st2 - 1))
//       1     2            21
// st1 = (7 + 3)
// st2 = (3 + 1)

// st1 * (10 / st3)
//       1        1
// st1 = (7 + 3)
// st2 = (3 + 1)
// st3 = (12 / st2 - 1)

// st1 * st4
// st1 = (7 + 3)
// st2 = (3 + 1)
// st3 = (12 / st2 - 1)
// st4 = (10 / st3)

// st1 * st4
// st1 = (7 + 3)
// st2 = (3 + 1)
// st3 = (st5 - 1)
// st4 = (10 / st3)
// st5 = 12 / st2
