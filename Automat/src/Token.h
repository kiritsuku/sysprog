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
    Ident,
    Number,
    KwIf,
    KwWhile,
    KwInt,
    KwWrite,
    KwRead,
    KwElse,
  };

  class Token {
  public:
    explicit Token(TokenType type, unsigned line, unsigned column);
    explicit Token(TokenType type, unsigned line, unsigned column, unsigned value, char *strvalue);
    explicit Token(TokenType type, unsigned line, unsigned column, Symbol *sym);
     ~Token();

    /** A string representation of this token. */
    const char *getValue();
    /** A string representation of the type of this token. */
    const char *typeText();
    /** The length of `text`. */
    unsigned textLen();

    TokenType getTokenType();
    unsigned getLine();
    unsigned getColumn();
    unsigned getInt();
    Symbol *symbol();

  private:
    TokenType type;
    Symbol *sym; // todo
    const char *strvalue;
    unsigned value;
    unsigned line;
    unsigned column;

  };

  /** The character value(s) this token type represents. */
  static const char *valueOf(TokenType t);

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
