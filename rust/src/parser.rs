use crate::lexer::Token;

pub struct AstNode {
	token: Token,
	left: AstNode,
	right: AstNode
}

