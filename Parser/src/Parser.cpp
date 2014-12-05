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

Nodes::Node *Parser::parse()
{
  return parseProg();
}

Nodes::Node *Parser::parseProg()
{
  auto decls = parseDecls();
  auto stmts = parseStatements();

  return new Nodes::Node(Nodes::Prog, decls, stmts);
}

Nodes::Node *Parser::parseDecls()
{
  if (token->getTokenType() != Tokens::KwInt) {
    return new Nodes::Node(Nodes::Nil);
  }

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
  accept(Tokens::KwInt);

  switch (token->getTokenType()) {
    case Tokens::LBracket: {
      auto arr = parseArray();
      auto ident = parseIdent();
      return new Nodes::Node(Nodes::DeclArray, arr, ident);
    }

    default: {
      auto ident = parseIdent();
      return new Nodes::Node(Nodes::DeclIdent, ident);
    }
  }
}

Nodes::Node *Parser::parseArray()
{
  accept(Tokens::LBracket);
  auto size = parseInt();
  accept(Tokens::RBracket);

  return new Nodes::Node(Nodes::Array, size);
}


Nodes::Node *Parser::parseStatements()
{
  if (token->getTokenType() == Tokens::Eof) {
    return new Nodes::Node(Nodes::Nil);
  }

  auto stmt = parseStatement();
  accept(Tokens::Semi);
  return new Nodes::Node(Nodes::Statements, stmt, parseStatements());
}

Nodes::Node *Parser::parseStatement()
{
  switch (token->getTokenType()) {
    case Tokens::Ident: {
      auto ident = parseIdent();
      auto idx = parseIndex();
      accept(Tokens::ColonEquals);
      auto exp = parseExp();
      return new Nodes::Node(Nodes::StatementIdent, ident, idx, exp);
    }
    case Tokens::KwWrite: {
      accept(Tokens::KwWrite);
      accept(Tokens::LParen);
      auto exp = parseExp();
      accept(Tokens::RParen);
      return new Nodes::Node(Nodes::StatementWrite, exp);
    }
    case Tokens::KwRead: {
      accept(Tokens::KwRead);
      accept(Tokens::LParen);
      auto ident = parseIdent();
      auto idx = parseIndex();
      accept(Tokens::RParen);
      return new Nodes::Node(Nodes::StatementWrite, idx, ident);
    }
    case Tokens::LBrace: {
      accept(Tokens::LBrace);
      auto stmts = parseStatements();
      accept(Tokens::RBrace);
      return new Nodes::Node(Nodes::Statements, stmts);
    }
    case Tokens::KwIf: {
      accept(Tokens::KwIf);
      accept(Tokens::LParen);
      auto exp = parseExp();
      accept(Tokens::RParen);
      auto ifStmt = parseStatement();

      if (token->getTokenType() == Tokens::KwElse) {
        accept(Tokens::KwElse);
        auto elseStmt = parseStatement();
        return new Nodes::Node(Nodes::StatementIf, exp, ifStmt, elseStmt);
      }
      return new Nodes::Node(Nodes::StatementIf, exp, ifStmt,
          new Nodes::Node(Nodes::Nil));
    }
    case Tokens::KwWhile: {
      accept(Tokens::KwWhile);
      accept(Tokens::LParen);
      auto exp = parseExp();
      accept(Tokens::RParen);
      auto stmt = parseStatement();
      return new Nodes::Node(Nodes::StatementWhile, exp, stmt);
    }
    default:
      err();
      // can't be reached
      return nullptr;
  }
  return nullptr;
}

Nodes::Node *Parser::parseExp()
{
  auto exp2 = parseExp2();
  auto op = parseOpExp();
  return new Nodes::Node(Nodes::Exp, exp2, op);
}

Nodes::Node *Parser::parseExp2()
{
  switch (token->getTokenType()) {
    case Tokens::LParen: {
      accept(Tokens::LParen);
      auto exp = parseExp();
      accept(Tokens::RParen);
      return new Nodes::Node(Nodes::Exp2, exp);
    }
    case Tokens::Ident: {
      auto ident = parseIdent();
      auto idx = parseIndex();
      return new Nodes::Node(Nodes::Exp2Ident, idx, ident);
    }
    case Tokens::Int: {
      auto i = parseInt();
      return new Nodes::Node(Nodes::Exp2Int, i);
    }
    case Tokens::Minus: {
      accept(Tokens::Minus);
      auto exp2 = parseExp2();
      return new Nodes::Node(Nodes::Exp2Minus, exp2);
    }
    case Tokens::Bang: {
      accept(Tokens::Bang);
      auto exp2 = parseExp2();
      return new Nodes::Node(Nodes::Exp2Neg, exp2);
    }
    default:
      err();
      // can't be reached
      return nullptr;
  }
}

Nodes::Node *Parser::parseIndex()
{
  if (token->getTokenType() != Tokens::LBracket) {
    return new Nodes::Node(Nodes::Nil);
  }

  accept(Tokens::LBracket);
  auto exp = parseExp();
  accept(Tokens::RBracket);

  return new Nodes::Node(Nodes::Index, exp);
}

Nodes::Node *Parser::parseOpExp()
{
  if (token->getTokenType() == Tokens::Eof) {
    return new Nodes::Node(Nodes::Nil);
  }

  auto op = parseOp();
  auto exp = parseExp();
  return new Nodes::Node(Nodes::OpExp, op, exp);
}

Nodes::Node *Parser::parseOp()
{
  switch (token->getTokenType()) {
    case Tokens::Plus:
    case Tokens::Minus:
    case Tokens::Mul:
    case Tokens::Div:
    case Tokens::Smaller:
    case Tokens::Greater:
    case Tokens::Equals:
    case Tokens::SmallerColonGreater:
    case Tokens::And:
      nextToken();
      return new Nodes::Node(Nodes::Op, token);

    default:
      return new Nodes::Node(Nodes::Nil);
  }
}

unsigned Parser::parseInt()
{
  if (token->getTokenType() != Tokens::Int) {
    err();
  }

  auto i = token->getInt();
  nextToken();
  return i;
}

Symbol *Parser::parseIdent()
{
  if (token->getTokenType() != Tokens::Ident) {
    err();
  }

  auto sym = token->symbol();
  nextToken();
  return sym;
}

void Parser::accept(Tokens::TokenType tpe)
{
  if (token->getTokenType() != tpe) {
    err();
  }
  nextToken();
}

void Parser::err()
{
  fprintf(stderr, "unexpected token '%s' at line '%d', column '%d'\n",
      token->getValue(), token->getLine(), token->getColumn());
  exit(1);
}

void Parser::nextToken()
{
  token = scanner.nextToken();
}
