#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"

Parser::Parser(Scanner &scanner, ErrorHandler &handler):
  scanner(scanner),
  handler(handler)
{
}

Parser::~Parser()
{
}

Nodes::Node *Parser::parseProg()
{
  auto decls = parseDecls();
  auto stmts = parseStatements();

  return new Nodes::Node(Nodes::Prog, decls, stmts);
}

Nodes::Node *Parser::parseDecls()
{
  auto decl = parseDecl();
  accept(Tokens::Semi);

  switch (decl->tpe()) {
    case Nodes::Nil:
      return decl;

    default:
      return new Nodes::Node(Nodes::Decls, parseDecls());
  }
}

Nodes::Node *Parser::parseDecl()
{
  if (strcmp(token->typeText(), "int") != 0) {
    return new Nodes::Node(Nodes::Nil);
  }

  accept(Tokens::Ident);
  auto arr = parseArray();
  auto ident = parseIdent();

  switch (arr->tpe()) {
    case Nodes::Nil:
      return new Nodes::Node(Nodes::DeclIdent, ident);

    default:
      return new Nodes::Node(Nodes::DeclArray, arr, ident);
  }
}

Nodes::Node *Parser::parseArray()
{
  if (token->getTokenType() != Tokens::LBracket)
    return new Nodes::Node(Nodes::Nil);

  accept(Tokens::LBracket);
  auto size = parseInt();
  accept(Tokens::RBracket);

  return new Nodes::Node(Nodes::Array, size);
}


Nodes::Node *Parser::parseStatements()
{
  return nullptr;
}

unsigned Parser::parseInt()
{
  accept(Tokens::Int);
  return token->getInt();
}

Symbol *Parser::parseIdent()
{
  accept(Tokens::Ident);
  return token->symbol();
}

void Parser::accept(Tokens::TokenType tpe)
{
  if (token->getTokenType() != tpe) {
    fprintf(stderr, "unexpected token '%s' at line '%d', column '%d'\n",
        token->getValue(), token->getLine(), token->getColumn());
    exit(1);
  }
  nextToken();
}

void Parser::nextToken()
{
  token = scanner.nextToken();
}
