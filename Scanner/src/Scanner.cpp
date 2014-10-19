#include "Scanner.h"

Tokens::Token Scanner::acceptChar(const char c)
{
  auto t = automat.accept(c);
  switch(t) {
    case Tokens::Eof:
      return t;

    case Tokens::Ignore:
      lastStart = buffer.offset();
      return acceptChar(buffer.nextChar());

    case Tokens::None:
      return acceptChar(buffer.nextChar());

    case Tokens::Ident: {
      auto ident = buffer.range(lastStart);
      auto kw = Tokens::instance().keyword(ident);
      lastStart = buffer.offset();

      if (kw != Tokens::None)
        return kw;
      else {
        // TODO create symbol in symboltable
        return Tokens::Ident;
      }
    }

    default: {
      auto len = Tokens::instance().textLen(t);
      lastStart += len;
      return t;
    }
  }
}

Tokens::Token Scanner::nextToken()
{
  auto c = buffer.currentChar();
  if (c == 0)
    return Tokens::Eof;
  else
    return acceptChar(c);
}
