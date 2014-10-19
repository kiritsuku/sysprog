#ifndef TOKEN_H_
#define TOKEN_H_

#include <string.h>

class Tokens final {
public:
  enum Token {
    None = 0,
    Ignore,
    Error,
    Eof,
    Int,
    Ident,

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
    While
  };

  static Tokens& instance();

  static const unsigned MaxToken = static_cast<unsigned>(While);

  Token tokenOf(unsigned char c);

  /**
   * Checks if `text` is a keyword. If this is the case the corresponding
   * token is returned. Otherwise `Token::None` is returned.
   */
  Token keyword(const char *text);
  unsigned textLen(const Token token);
  const char* text(const Token token);

private:
  const char* tokenString[MaxToken+1];

  void enter(Token token, const char* repr);

  Tokens() {
    enter(None, "<none>");
    enter(Ignore, "<ignore>");
    enter(Error, "<error>");
    enter(Eof, "<eof>");
    enter(Int, "<int>");
    enter(Ident, "<ident>");

    enter(Plus, "+");
    enter(Minus, "-");
    enter(Div, "/");
    enter(Mul, "*");
    enter(Smaller, "<");
    enter(Greater, ">");
    enter(Equals, "=");
    enter(ColonEquals, ":=");
    enter(SmallerColonGreater, "<:>");
    enter(Bang, "!");
    enter(And, "&");
    enter(LParen, "(");
    enter(RParen, ")");
    enter(LBrace, "{");
    enter(RBrace, "}");
    enter(LBracket, "[");
    enter(RBracket, "]");

    enter(If, "if");
    enter(While, "while");
  }
  // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
  Tokens(Tokens const&);
  void operator=(Tokens const&);
};

#endif
