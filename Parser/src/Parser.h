#ifndef PARSER_H_
#define PARSER_H_

#include "Token.h"
#include "Scanner.h"
#include "Symboltable.h"
#include "ErrorHandler.h"

class Parser final {
public:
  Parser(Scanner &scanner, ErrorHandler &handler);
  ~Parser();

private:
  Scanner &scanner;
  ErrorHandler &handler;
};

#endif
