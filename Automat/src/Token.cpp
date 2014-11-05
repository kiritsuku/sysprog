#include <string.h>
#include "Token.h"

Tokens::Token::Token()
{
}

Tokens::Token::~Token()
{
}

unsigned Tokens::Token::textLen()
{
  return strlen(text());
}

bool Tokens::Token::isIdent()
{
  return false;
}

bool Tokens::Token::isInt()
{
  return false;
}

Tokens::NoneToken *const Tokens::None = new NoneToken();
Tokens::IgnoreToken *const Tokens::Ignore = new IgnoreToken();
Tokens::ErrorToken *const Tokens::Error = new ErrorToken();
Tokens::EofToken *const Tokens::Eof = new EofToken();
Tokens::IntToken *const Tokens::Int = new IntToken();
Tokens::StrToken *const Tokens::Str = new StrToken();
Tokens::PlusToken *const Tokens::Plus = new PlusToken();
Tokens::MinusToken *const Tokens::Minus = new MinusToken();
Tokens::DivToken *const Tokens::Div = new DivToken();
Tokens::MulToken *const Tokens::Mul = new MulToken();
Tokens::SmallerToken *const Tokens::Smaller = new SmallerToken();
Tokens::GreaterToken *const Tokens::Greater = new GreaterToken();
Tokens::EqualsToken *const Tokens::Equals = new EqualsToken();
Tokens::ColonEqualsToken *const Tokens::ColonEquals = new ColonEqualsToken();
Tokens::SmallerColonGreaterToken *const Tokens::SmallerColonGreater = new SmallerColonGreaterToken();
Tokens::BangToken *const Tokens::Bang = new BangToken();
Tokens::AndToken *const Tokens::And = new AndToken();
Tokens::SemiToken *const Tokens::Semi = new SemiToken();
Tokens::LParenToken *const Tokens::LParen = new LParenToken();
Tokens::RParenToken *const Tokens::RParen = new RParenToken();
Tokens::LBraceToken *const Tokens::LBrace = new LBraceToken();
Tokens::RBraceToken *const Tokens::RBrace = new RBraceToken();
Tokens::LBracketToken *const Tokens::LBracket = new LBracketToken();
Tokens::RBracketToken *const Tokens::RBracket = new RBracketToken();
Tokens::IfToken *const Tokens::If = new IfToken();
Tokens::WhileToken *const Tokens::While = new WhileToken();

Tokens::IdentToken *Tokens::createIdent(Symbol &sym)
{
  return new IdentToken(sym);
}

Tokens::NumberToken *Tokens::createNumber(unsigned value, char *strvalue)
{
  return new NumberToken(value, strvalue);
}

Tokens::Token *Tokens::keyword(const char *text)
{
  if (strcmp(text, "if") == 0 || strcmp(text, "IF") == 0)
    return If;
  else if (strcmp(text, "while") == 0 || strcmp(text, "WHILE") == 0)
    return While;
  else
    return None;
}

Tokens::Token *Tokens::tokenOf(unsigned char c)
{
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

Tokens::IdentToken::IdentToken(Symbol& sym):
  Tokens::Token(),
  sym(sym)
{
}

const char *Tokens::IdentToken::text()
{
  return sym.ident;
}

bool Tokens::IdentToken::isIdent()
{
  return true;
}

Tokens::NumberToken::NumberToken(unsigned value, char *strvalue):
  Tokens::Token(),
  value(value),
  strvalue(strvalue)
{
  char *s = new char[strlen(strvalue)+1];
  strcpy(s, strvalue);
  this->strvalue = s;
}

Tokens::NumberToken::~NumberToken()
{
  delete[] strvalue;
}

const char *Tokens::NumberToken::text()
{
  return strvalue;
}

bool Tokens::NumberToken::isInt()
{
  return true;
}
