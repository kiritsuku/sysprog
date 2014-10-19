#ifndef SCANNER_H_
#define SCANNER_H_

#include "Token.h"
#include "Automat.h"
#include "Buffer.h"

static const unsigned SCANNER_BUFFER_SIZE = 100;

class Scanner final {
public:
	Scanner(Automat &automat, Buffer &buffer):
    automat(automat),
    buffer(buffer),
    lastStart(0) {}
	~Scanner() {}

  Tokens::Token nextToken();

private:
  Automat &automat;
  Buffer &buffer;
  unsigned lastStart;

  Tokens::Token acceptChar(const char c);
};

#endif
