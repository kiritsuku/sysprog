#ifndef PARSER_H_
#define PARSER_H_

#include "Token.h"
#include "Scanner.h"
#include "Symboltable.h"
#include "ErrorHandler.h"
#include "Nodes.h"

class Parser final {
public:
  Parser(Scanner &scanner, ErrorHandler &handler);
  ~Parser();

private:
  Scanner &scanner;
  ErrorHandler &handler;

  Tokens::Token *token;

  Nodes::Node *parseProg();
  Nodes::Node *parseDecls();
  Nodes::Node *parseStatements();
  Nodes::Node *parseDecl();
  Nodes::Node *parseArray();
  unsigned parseInt();
  Symbol *parseIdent();

  void accept(Tokens::TokenType tpe);
  void nextToken();
};

#endif
