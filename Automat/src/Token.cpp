#include <string.h>
#include "Token.h"

Tokens::Token::Token(TokenType type, unsigned line, unsigned column):
  type(type),
  sym(nullptr),
  strvalue(nullptr),
  value(0),
  line(line),
  column(column)
{
}

Tokens::Token::Token(TokenType type, unsigned line, unsigned column, Symbol *sym):
  type(type),
  sym(sym),
  strvalue(nullptr),
  value(0),
  line(line),
  column(column)
{
}

Tokens::Token::Token(TokenType type, unsigned line, unsigned column, unsigned value, char *strvalue):
  type(type),
  sym(nullptr),
  value(value),
  line(line),
  column(column)
{
  char *s = new char[strlen(strvalue)+1];
  strcpy(s, strvalue);
  this->strvalue = s;
}

Tokens::Token::~Token()
{
  if (this->getTokenType() == Ident || this->getTokenType() == Number) {
    delete[] this->strvalue;
  }
}

unsigned Tokens::Token::getLine()
{
  return line;
}

unsigned Tokens::Token::getColumn()
{
  return column;
}

unsigned Tokens::Token::getInt()
{
  return value;
}

Symbol *Tokens::Token::symbol()
{
  return sym;
}

const char* Tokens::Token::typeText()
{
  switch (this->type) {
    case None:
      return "<none>";
    case Ignore:
      return "<ignore>";
    case Error:
      return "<error>";
    case Eof:
      return "<eof>";
    case Int:
      return "<int>";
    case Str:
      return "<str>";
    case Plus:
      return "Plus";
    case Minus:
      return "Minus";
    case Div:
      return "Div";
    case Mul:
      return "Mul";
    case Smaller:
      return "Smaller";
    case Greater:
      return "Greater";
    case Equals:
      return "Equals";
    case ColonEquals:
      return "ColonEquals";
    case SmallerColonGreater:
      return "SmallerColonGreater";
    case Bang:
      return "Bang";
    case And:
      return "And";
    case Semi:
      return "Semi";
    case LParen:
      return "LParen";
    case RParen:
      return "RParen";
    case LBrace:
      return "LBrace";
    case RBrace:
      return "RBrace";
    case LBracket:
      return "LBracket";
    case RBracket:
      return "RBracket";
    case KwIf:
      return "If";
    case KwElse:
      return "Else";
    case KwWhile:
      return "While";
    case KwWrite:
      return "Write";
    case KwRead:
      return "Read";
    case KwInt:
      return "Int";
    case Ident:
      return "Ident";
    case Number:
      return "Number";
  }
}

const char* Tokens::Token::getValue()
{
  switch (this->type) {
    case Ident:
      return this->sym->ident;
    case Number:
      return this->strvalue;
    default:
      return valueOf(this->type);
  }
}

const char *Tokens::valueOf(TokenType t)
{
  switch (t) {
    case None:
      return "<none>";
    case Ignore:
      return "<ignore>";
    case Error:
      return "<error>";
    case Eof:
      return "<eof>";
    case Int:
      return "<int>";
    case Str:
      return "<str>";
    case Plus:
      return "+";
    case Minus:
      return "-";
    case Div:
      return "/";
    case Mul:
      return "*";
    case Smaller:
      return "<";
    case Greater:
      return ">";
    case Equals:
      return "=";
    case ColonEquals:
      return ":=";
    case SmallerColonGreater:
      return "<:>";
    case Bang:
      return "!";
    case And:
      return "&";
    case Semi:
      return ";";
    case LParen:
      return "(";
    case RParen:
      return ")";
    case LBrace:
      return "{";
    case RBrace:
      return "}";
    case LBracket:
      return "[";
    case RBracket:
      return "]";
    case KwIf:
      return "if";
    case KwElse:
      return "else";
    case KwWhile:
      return "while";
    case KwWrite:
      return "write";
    case KwRead:
      return "read";
    case KwInt:
      return "int";
    case Ident:
      return "<ident>";
    case Number:
      return "<number>";
  }
}

unsigned Tokens::Token::textLen()
{
  return strlen(getValue());
}

Tokens::TokenType Tokens::Token::getTokenType()
{
  return this->type;
}

Tokens::TokenType Tokens::keyword(const char *text)
{
  if (strcmp(text, "if") == 0 || strcmp(text, "IF") == 0)
    return KwIf;
  else if (strcmp(text, "else") == 0 || strcmp(text, "ELSE") == 0)
    return KwElse;
  else if (strcmp(text, "while") == 0 || strcmp(text, "WHILE") == 0)
    return KwWhile;
  else if (strcmp(text, "int") == 0)
    return KwInt;
  else if (strcmp(text, "write") == 0)
    return KwWrite;
  else if (strcmp(text, "read") == 0)
    return KwRead;
  else
    return None;
}

Tokens::TokenType Tokens::tokenOf(unsigned char c)
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
