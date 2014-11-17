#ifndef TOKEN_H_
#define TOKEN_H_

#include <Symboltable.h>

class Tokens final {

public:

	enum TokenType{
		None,
		Ignore,
		Error,
		Eof,
		Int,
		Str,
		Plus,
		Minus,
		Div,
		Mul,
		Smaller,
		Greater,
		Equals,
		ColonEquals,
		SmallerColonGreater,
		Bang,
		And,
		Semi,
		LParen,
		RParen,
		LBrace,
		RBrace,
		LBracket,
		RBracket,
		If,
		While,
		Ident,
		Number
	};

  class Token {
  public:
    explicit Token(TokenType type, unsigned offset);
    explicit Token(TokenType type, unsigned offset, unsigned value, char *strvalue);
    explicit Token(TokenType type, unsigned offset, Symbol *sym);
     ~Token();

    /** The text that is represented by this token. */
    const char *text();
    /** The length of `text`. */
    unsigned textLen();
    /** Returns `true` if this token represents an identifier. */
    bool isIdent();
    /** Returns `true` if this token represents an int. */
    bool isInt();

    TokenType getTokenType ();
    unsigned getOffset();

  private:
    TokenType type;
    Symbol *sym; // todo
    const char *strvalue;
    unsigned value;
    unsigned offset;

  };

  static Token *createIdent(Symbol &sym);
  static Token *createNumber(unsigned value, char *strvalue);

  /**
   * Returns the token that corresponds to `c` or `Token::Error` if none
   * correspondence exists.
   */
  static TokenType tokenOf(unsigned char c);

  /**
   * Checks if `text` is a keyword. If this is the case the corresponding
   * token is returned. Otherwise `Token::None` is returned.
   */
  static TokenType keyword(const char *text);
};

#endif
