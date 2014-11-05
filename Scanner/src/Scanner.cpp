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
    return Tokens::Error;
  }
  return Tokens::createNumber(value, str);
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
    return kw;
  auto sym = symboltable.create(str);
  return Tokens::createIdent(*sym);
}

Tokens::Token *Scanner::acceptChar(const char c)
{
  lastOffset = lastStart;

  if (c == 0)
    return Tokens::Eof;

  auto t = automat.accept(c);

  if (t == Tokens::Error) {
    handler.addError(lastOffset, "invalid character");
    buffer.nextChar();
    lastStart = buffer.offset();
    return t;
  }

  else if (t == Tokens::Ignore) {
    auto c = buffer.nextChar();
    lastStart = buffer.offset();
    return acceptChar(c);
  }

  else if (t == Tokens::None)
    return acceptChar(buffer.nextChar());

  else if (t == Tokens::Int)
    return createNumber();

  else if (t == Tokens::Str)
    return createIdent();

  else {
    auto len = t->textLen();
    lastStart += len;
    buffer.setOffset(lastStart);
    return t;
  }
}

Tokens::Token *Scanner::nextToken()
{
  auto c = buffer.currentChar();
  if (c == 0)
    return Tokens::Eof;

  return acceptChar(c);
}
