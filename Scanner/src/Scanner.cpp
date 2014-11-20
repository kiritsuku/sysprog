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
  lastStart(0)
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
  auto col = getColumn();
  lastStart += len;

  errno = 0;
  auto value = strtol(str, 0, 10);
  if (errno == ERANGE) {
    handler.addError(start, "number too large");
    return  new Tokens::Token(Tokens::Error, buffer.currentLine(), col);
  }
  return new Tokens::Token(Tokens::Number, buffer.currentLine(), col, value, str);
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
    return new Tokens::Token(kw, buffer.currentLine(), col);
  auto sym = symboltable.create(str);
  return new Tokens::Token(Tokens::Ident, buffer.currentLine(), col, sym);
}

unsigned Scanner::getColumn()
{
  auto diff = buffer.offset()-lastStart;
  return buffer.currentColumn()-diff;
}

Tokens::Token *Scanner::acceptChar(const char c)
{
  if (c == 0)
    return new Tokens::Token(Tokens::Eof, buffer.currentLine(), getColumn());

  auto t = automat.accept(c);
  switch(t) {
    case Tokens::Error: {
      handler.addError(lastStart, "invalid character");
      auto col = getColumn();
      auto len = buffer.offset()-lastStart;
      // we only have to read the next char if a single char is invalid
      if (len == 0)
        buffer.nextChar();
      lastStart = buffer.offset();
      return new Tokens::Token(t, buffer.currentLine(), col);
    }
    case Tokens::Ignore: {
       auto c = buffer.nextChar();
       lastStart = buffer.offset();
       return acceptChar(c);
    }
    case Tokens::None:
      return acceptChar(buffer.nextChar());
    case Tokens::Int:
      return createNumber();
    case Tokens::Str:
      return createIdent();
    default: {
      Tokens::Token *tmp = new Tokens::Token(t, buffer.currentLine(), getColumn());
      auto len = tmp->textLen();
      lastStart += len;
      buffer.setOffset(lastStart);
      return tmp;
    }
  }
}

Tokens::Token *Scanner::nextToken()
{
  auto c = buffer.currentChar();
  if (c == 0)
    return  new Tokens::Token(Tokens::Eof, buffer.currentLine(), getColumn());

  return acceptChar(c);
}
