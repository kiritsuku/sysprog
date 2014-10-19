#include "Token.h"

Tokens& Tokens::instance()
{
  static Tokens ins;
  return ins;
}

unsigned Tokens::textLen(const Token token)
{
  auto repr = tokenString[static_cast<unsigned>(token)];
  return strlen(repr);
}

const char* Tokens::text(const Token token)
{
  return tokenString[static_cast<unsigned>(token)];
}

Tokens::Token Tokens::keyword(const char *text)
{
  if (strcmp(text, "if") == 0 || strcmp(text, "IF") == 0)
    return Tokens::If;
  else if (strcmp(text, "while") == 0 || strcmp(text, "WHILE") == 0)
    return Tokens::While;
  else
    return Tokens::None;
}

Tokens::Token Tokens::tokenOf(unsigned char c)
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

void Tokens::enter(Token token, const char* repr)
{
  tokenString[static_cast<unsigned>(token)] = repr;
}

