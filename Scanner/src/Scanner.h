#ifndef SCANNER_H_
#define SCANNER_H_

#include "Token.h"
#include "Automat.h"
#include "Buffer.h"
#include "Symboltable.h"

static const unsigned SCANNER_BUFFER_SIZE = 100;

class Scanner final {
public:
	Scanner(Automat &automat, Buffer &buffer, Symboltable &symboltable):
    automat(automat),
    buffer(buffer),
    symboltable(symboltable),
    lastStart(0) {}
	~Scanner() {}

  Tokens::Token *nextToken();

private:
  Automat &automat;
  Buffer &buffer;
  Symboltable &symboltable;
  unsigned lastStart;

  Tokens::Token *acceptChar(const char c);
  Tokens::Token *createNumber();
  Tokens::Token *createIdent();
};

#endif
