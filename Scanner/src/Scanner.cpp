#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "Scanner.h"

Scanner::Scanner(Automat &automat, Buffer &buffer, Symboltable &symboltable, ErrorHandler &handler):
  automat(automat),
  buffer(buffer),
  symboltable(symboltable),
  handler(handler),
  lastStart(0),
  lastOffset(0)
{
}

Scanner::~Scanner()
{
}

unsigned Scanner::offset()
{
  return lastOffset;
}

Tokens::Token *Scanner::createNumber()
{
  unsigned start = lastStart;
  unsigned len = buffer.offset()-start;
  char str[len+1];
  buffer.range(str, start, len);
  lastStart += len;

  errno = 0;
  auto value = strtol(str, 0, 10);
  if (errno == ERANGE) {
    handler.addError(start, "number too large");
    return  new Tokens::Token ( Tokens::Error);
  }
  return new Tokens::Token(Tokens::Number,value, str);
}

Tokens::Token *Scanner::createIdent()
{
  unsigned start = lastStart;
  unsigned len = buffer.offset()-start;
  char str[len+1];
  buffer.range(str, start, len);
  lastStart += len;

  auto kw = Tokens::keyword(str);
  if (kw != Tokens::None)
    return new Tokens::Token(kw);
  auto sym = symboltable.create(str);
  return new Tokens::Token (Tokens::Ident , sym);
}

Tokens::Token *Scanner::acceptChar(const char c)
{
  lastOffset = lastStart;

  if (c == 0)
    return new Tokens::Token(Tokens::Eof);

  auto t = automat.accept(c);
  switch(t){

  case Tokens::Error:{
	  handler.addError(lastOffset, "invalid character");
	  buffer.nextChar();
	  lastStart = buffer.offset();
	  return new Tokens::Token (t);}
  case Tokens::Ignore:{
	   auto c = buffer.nextChar();
	   lastStart = buffer.offset();
	   return acceptChar(c);}
  case Tokens::None:
	  return acceptChar(buffer.nextChar());
  case Tokens::Int:
	  return createNumber();
  case Tokens::Str:
	  return createIdent();
  default:{
	   Tokens::Token *tmp = new Tokens::Token (t);
	   auto len = tmp->textLen();
	   lastStart += len;
	   buffer.setOffset(lastStart);
	   return tmp;}
  }
}

Tokens::Token *Scanner::nextToken()
{
  auto c = buffer.currentChar();
  if (c == 0)
    return  new Tokens::Token(Tokens::Eof);

  return acceptChar(c);
}
