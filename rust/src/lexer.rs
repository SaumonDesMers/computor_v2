
pub struct Lexer {
	pub tokens: Vec<Token>
}

pub struct Token {
	pub r#type: TokenType,
	pub value: String,
}

pub enum TokenType {
	Number,
	Variable,
	Operator,
	Punctuation
}