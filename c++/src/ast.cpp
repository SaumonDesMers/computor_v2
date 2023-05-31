#include <cstring>
#include <algorithm>
#include <list>
#include "ast.hpp"
#include "error.hpp"

// ##############################################################################
// #                                                                            #
// #                                Class AstNode                               #
// #                                                                            #
// ##############################################################################

AstNode::AstNode(): token(Token()), left(NULL), right(NULL), brace(false) {}
AstNode::AstNode(Token _token, AstNode *_left = NULL, AstNode *_right = NULL, bool _brace = false)
	: token(_token), left(_left), right(_right), brace(_brace) {}

AstNode::~AstNode() {
	delete this->left;
	delete this->right;
}

void AstNode::log(int depth) {
	cout << string(depth, '\t')
		<< "{raw: " << this->token.raw
		<< ", left: " << (this->left ? this->left->token.raw : "null")
		<< ", right: " << (this->right ? this->right->token.raw : "null")
		<< "}" << endl;
	if (this->left)
		this->left->log(depth+1);
	if (this->right)
		this->right->log(depth+1);
}

string AstNode::to_string() {
	string str = "";
	if (this->brace)
		str += "(";
	if (this->left)
		str += this->left->to_string() + " ";
	str += this->token.raw;
	if (this->right)
		str += " " + this->right->to_string();
	if (this->brace)
		str += ")";
	return str;
}

// ##############################################################################
// #                                                                            #
// #                                Class AstTree                               #
// #                                                                            #
// ##############################################################################

AstTree::AstTree(Lexer &lex): root(NULL), lexer(lex) {
	try {
		list<AstNode *> nodeList = this->getNodeList(lex.tokens);
		this->root = this->parseToken(nodeList);

		// remove brace from root node
		this->root->brace = false;
		
	} catch (string err) {
		panic(err);
	}
}

AstTree::~AstTree() {
	delete this->root;
}

list<AstNode *> AstTree::getNodeList(TokenList &tokens) {
	list<AstNode *> nodeList;

	for (Token &token: tokens)
		nodeList.push_back(new AstNode(token));

	return nodeList;
}

AstNode *AstTree::parseToken(list<AstNode *> nodeList) {

	while (true) {
		
		// find the first brace
		auto firstBrace_it = find_if(nodeList.begin(), nodeList.end(), [](AstNode *node) {
			return node->token.type & BRACE;
		});

		// if there is no brace, go to the parsing
		if (firstBrace_it == nodeList.end())
			break;

		// error if first brace is a right brace
		if ((*firstBrace_it)->token.type == RBRACE)
			invalidSyntax(this->lexer.input, (*firstBrace_it)->token.index);

		// find matching right brace (e.i. the next right brace with the same depth)
		auto matchingEndBrace_it = nodeList.end();
		int depth = -1;
		for (auto it = firstBrace_it; it != nodeList.end(); it++) {
			AstNode *node = *it;
			if (node->token.type == LBRACE)
				depth++;
			else if (node->token.type == RBRACE) {
				if (depth == 0) {
					matchingEndBrace_it = it;
					break;
				} else
					depth--;
			}
		}

		// error if there is no matching brace
		if (matchingEndBrace_it == nodeList.end())
			invalidSyntax(this->lexer.input, (*firstBrace_it)->token.index);
		
		// recursion with the nested braces
		AstNode *node = this->parseToken(list<AstNode *>(++firstBrace_it, matchingEndBrace_it));

		if (node == NULL)
			panic("ParseToken return NULL.");

		// replace nested braces with the root node
		nodeList.erase(--firstBrace_it, ++matchingEndBrace_it);
		nodeList.insert(matchingEndBrace_it, node);

	}

	// filter from the nodes the operators which has been parsed yet (e.i. those who don't have childs)
	vector<list<AstNode *>::iterator> operators;
	for (auto it = nodeList.begin(); it != nodeList.end(); it++)
		if ((*it)->token.type & OPERATOR && (*it)->left == NULL)
			operators.push_back(it);
	
	// sort operator by priority
	sort(operators.begin(), operators.end(), [](auto it1, auto it2) {
		return priority((*it1)->token.type) > priority((*it2)->token.type);
	});

	// for each operator in order of priority, remove its neighbours from the list and put them as its childs
	for (auto &it: operators) {
		auto prev = it; prev--;
		auto next = it; next++;
		(*it)->left = *prev;
		(*it)->right = *next;
		nodeList.erase(prev);
		nodeList.erase(next);
	}

	// put brace around the tree
	(*nodeList.begin())->brace = true;

	return *nodeList.begin();
}
