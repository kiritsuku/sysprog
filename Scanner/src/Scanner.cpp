#include <string.h>
#include "Scanner.h"

Tokens::Token *Scanner::acceptChar(const char c)
{
  auto t = automat.accept(c);

  if (t == Tokens::Eof)
    return t;

  else if (t == Tokens::Ignore) {
    lastStart = buffer.offset();
    return acceptChar(buffer.nextChar());
  }

  else if (t == Tokens::None)
    return acceptChar(buffer.nextChar());

  else if (t == Tokens::Int) {
    auto strvalue = buffer.range(lastStart);
    lastStart += strlen(strvalue);
    buffer.setOffset(lastStart);
    // TODO create int value here
    delete[] strvalue;
    return Tokens::Int;
  }

  else if (t == Tokens::Str) {
    auto ident = buffer.range(lastStart);
    auto kw = Tokens::keyword(ident);
    lastStart = buffer.offset();
    delete[] ident;

    if (kw != Tokens::None)
      return kw;
    else {
      // TODO create symbol in symboltable
      return Tokens::Str;
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
