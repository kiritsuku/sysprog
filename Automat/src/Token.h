#ifndef TOKEN_H_
#define TOKEN_H_

#include <string.h>

class Tokens {
public:
  static Tokens& instance() {
    static Tokens ins;
    return ins;
  }

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

  static const unsigned MaxToken = static_cast<unsigned>(While);

  static Token tokenOf(unsigned char c) {
    switch(c) {
      case '+': return Plus;
      case '-': return Minus;
      case '/': return Div;
      case '*': return Mul;
      case '<': return Smaller;
      case '>': return Greater;
      case '=': return Equals;
      case '!': return Bang;
      case '&': return And;
      case ';': return Semi;
      case '(': return LParen;
      case ')': return RParen;
      case '{': return LBrace;
      case '}': return RBrace;
      case '[': return LBracket;
      case ']': return RBracket;
      default : return Error;
    }
  }

  unsigned textLen(const Token token) {
    auto repr = tokenString[static_cast<unsigned>(token)];
    return strlen(repr);
  }

  const char* text(const Token token) {
    return tokenString[static_cast<unsigned>(token)];
  }

private:
  const char* tokenString[MaxToken+1];

  void enter(Token token, const char* repr) {
    tokenString[static_cast<unsigned>(token)] = repr;
  }

  Tokens() {
    enter(None, "<none>");
    enter(Ignore, "<ignore>");
    enter(Error, "<error>");
    enter(Eof, "<eof>");
    enter(Int, "<intlit>");
    enter(Ident, "<stringlit>");

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
