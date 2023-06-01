use crate::lexer::Token;

pub struct Node {
	token: Token,
	left: Node,
	right: Node
}

