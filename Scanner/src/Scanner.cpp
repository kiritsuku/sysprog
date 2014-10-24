#include <string.h>
#include "Scanner.h"

Tokens::Token *Scanner::acceptChar(const char c)
{
  auto t = automat.accept(c);

  if (t == Tokens::Eof)
    return t;

  else if (t == Tokens::Ignore) {
    auto c = buffer.nextChar();
    lastStart = buffer.offset();
    return acceptChar(c);
  }

  else if (t == Tokens::None)
    return acceptChar(buffer.nextChar());

  else if (t == Tokens::Int) {
    unsigned start = lastStart;
    unsigned len = buffer.offset()-start;
    char strvalue[len+1];
    buffer.range(strvalue, start, len);
    lastStart += strlen(strvalue);
    buffer.setOffset(lastStart);
    // TODO create int value here
    return Tokens::Int;
  }

  else if (t == Tokens::Str) {
    unsigned start = lastStart;
    unsigned len = buffer.offset()-start;
    char ident[len+1];
    buffer.range(ident, start, len);

    auto kw = Tokens::keyword(ident);
    lastStart = buffer.offset();

    if (kw != Tokens::None)
      return kw;
    else {
      auto sym = symboltable.create(ident);
      // TODO free memory
      return Tokens::createIdent(start, (char*) (sym->ident));
    }
  }

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
