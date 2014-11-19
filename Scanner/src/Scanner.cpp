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
  lastOffset(0),
  column(1),
  lines(1),
  lastLine(0)
{
}

Scanner::~Scanner()
{
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
    return  new Tokens::Token(Tokens::Error, lastLine, getColumn());
  }
  return new Tokens::Token(Tokens::Number, lastLine, getColumn(), value, str);
}

Tokens::Token *Scanner::createIdent()
{
  unsigned start = lastStart;
  unsigned len = buffer.offset()-start;
  char str[len+1];
  buffer.range(str, start, len);
  auto col = getColumn();
  lastStart += len;

  auto kw = Tokens::keyword(str);
  if (kw != Tokens::None)
    return new Tokens::Token(kw, lastLine, col);
  auto sym = symboltable.create(str);
  return new Tokens::Token(Tokens::Ident, lastLine, col, sym);
}

unsigned Scanner::getColumn()
{
  auto diff = buffer.offset()-lastStart;
  return column-diff;
}

Tokens::Token *Scanner::acceptChar(const char c)
{
  lastOffset = lastStart;

  column++;
  lastLine = lines;
  if (c == '\n') {
    lines++;
    column = 1;
  }

  if (c == 0)
    return new Tokens::Token(Tokens::Eof, lastLine, getColumn());

  auto t = automat.accept(c);
  switch(t){

  case Tokens::Error:{
	  handler.addError(lastOffset, "invalid character");
    auto col = getColumn();
	  buffer.nextChar();
	  lastStart = buffer.offset();
	  return new Tokens::Token(t, lastLine, col);}
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
	   Tokens::Token *tmp = new Tokens::Token(t, lastLine, getColumn());
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
    return  new Tokens::Token(Tokens::Eof, lastLine, getColumn());

  return acceptChar(c);
}
