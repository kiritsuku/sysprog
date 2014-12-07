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

  /**
   * Prints an error message about an unexpected token and terminates the
   * program. Can show a number of tokens that are expected instead.
   *
   * Expects a variable number of TokenType arguments.
   * `count` is the number of arguments that are passed to this function.
   */
  void err(unsigned count, ...);
  void nextToken();
};

#endif
