#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Scanner.h"

Scanner::Scanner(Automat &automat, Buffer &buffer, Symboltable &symboltable):
  automat(automat),
  buffer(buffer),
  symboltable(symboltable),
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
  lastStart += len;

  auto value = strtol(str, 0, 10);
  if (value == 0 && errno == ERANGE)
    return Tokens::Error;
  return Tokens::createNumber(start, value, str);
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
  return Tokens::createIdent(start, *sym);
}

Tokens::Token *Scanner::acceptChar(const char c)
{
  if (c == 0)
    return Tokens::Eof;

  auto t = automat.accept(c);

  if (t == Tokens::Error) {
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
  else
    return acceptChar(c);
}
