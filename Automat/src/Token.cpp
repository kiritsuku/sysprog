#include <string.h>
#include "Token.h"

Tokens::Token::Token(TokenType type, unsigned line, unsigned column)
{
	this->type=type;
  this->line = line;
  this->column=column;
	this->value=0;
	this->sym=NULL;
	this->strvalue=NULL;




}
Tokens::Token::Token(TokenType type, unsigned line, unsigned column, Symbol *sym)
{
	this->type=type;
  this->line = line;
  this->column=column;
	this->value=0;
	this->sym = sym;
	this->strvalue=NULL;
}
Tokens::Token::Token(TokenType type, unsigned line, unsigned column, unsigned value, char *strvalue)
{
	this->type=type;
  this->line = line;
  this->column=column;
	this->sym= NULL;

	this->value=value;


	char *s = new char[strlen(strvalue)+1];
	strcpy(s, strvalue);
	this->strvalue = s;



}

Tokens::Token::~Token()
{
	if (this->getTokenType() == Ident || this->getTokenType() == Number){
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

const char* Tokens::Token::typeText()
{
	switch ( this->type ){
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
	case If:
		return "If";
	case While:
		return "While";
	case Ident:
		return "Ident";
	case Number:
		return "Number";

	}
}
const char* Tokens::Token::getValue()
{
	switch (this->type ){
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
	case If:
		return "if";
	case While:
		return "while";
	case Ident:
		return this->sym->ident;
	case Number:
		return this->strvalue;
	}
}

unsigned Tokens::Token::textLen()
{
  return strlen(getValue());
}

bool Tokens::Token::isIdent()
{
  return (this->type == Ident);
}

bool Tokens::Token::isInt()
{
	return(this->type == Number);
}

Tokens::TokenType Tokens::Token::getTokenType (){
	return this->type;
}

Tokens::TokenType Tokens::keyword(const char *text)
{
  if (strcmp(text, "if") == 0 || strcmp(text, "IF") == 0)
    return If;
  else if (strcmp(text, "while") == 0 || strcmp(text, "WHILE") == 0)
    return While;
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
