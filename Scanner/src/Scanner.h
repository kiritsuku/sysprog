#ifndef SCANNER_H_
#define SCANNER_H_

#include "Token.h"
#include "Automat.h"
#include "Buffer.h"
#include "Symboltable.h"
#include "ErrorHandler.h"

class Scanner final {
public:
	Scanner(Automat &automat, Buffer &buffer, Symboltable &symboltable, ErrorHandler &handler);
	~Scanner();

  /**
   * Returns the next token. Doesn't return token that represent
   * whitespace or comments.
   *
   * Returns `Tokens::Eof` if the buffer is empty.
   */
  Tokens::Token *nextToken();

private:


  Automat &automat;
  Buffer &buffer;
  Symboltable &symboltable;
  ErrorHandler &handler;
  unsigned lastStart;
  unsigned lastOffset;

  Tokens::Token *acceptChar(const char c);
  Tokens::Token *createNumber();
  Tokens::Token *createIdent();
};

#endif
