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

  Nodes::Node *parse();

private:
  Scanner &scanner;
  ErrorHandler &handler;

  Tokens::Token *token;

  Nodes::Node *parseProg();
  Nodes::Node *parseDecls();
  Nodes::Node *parseDecl();
  Nodes::Node *parseArray();
  Nodes::Node *parseStatements();
  Nodes::Node *parseStatement();
  Nodes::Node *parseExp();
  Nodes::Node *parseExp2();
  Nodes::Node *parseIndex();
  Nodes::Node *parseOpExp();
  Nodes::Node *parseOp();
  unsigned parseInt();
  Symbol *parseIdent();

  void accept(Tokens::TokenType tpe);
  void err();
  void nextToken();
};

#endif
