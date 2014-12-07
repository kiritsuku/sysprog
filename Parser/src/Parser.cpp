#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Parser.h"

Parser::Parser(Scanner &scanner, ErrorHandler &handler):
  scanner(scanner),
  handler(handler),
  token(nullptr)
{
}

Parser::~Parser()
{
  if (token != nullptr)
    delete token;
}

Nodes::Node *Parser::parse()
{
  nextToken();
  return parseProg();
}

Nodes::Node *Parser::parseProg()
{
  auto decls = parseDecls();
  auto stmts = parseStatements();
  accept(Tokens::Eof);

  return new Nodes::Node(Nodes::Prog, decls, stmts);
}

Nodes::Node *Parser::parseDecls()
{
  if (token->getTokenType() != Tokens::KwInt) {
    return new Nodes::Node(Nodes::Nil);
  }

  auto decl = parseDecl();
  accept(Tokens::Semi);
  return new Nodes::Node(Nodes::Decls, decl, parseDecls());
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
  switch (token->getTokenType()) {
    case Tokens::Ident:
    case Tokens::KwWrite:
    case Tokens::KwRead:
    case Tokens::LBrace:
    case Tokens::KwIf:
    case Tokens::KwWhile:
      break;
    default:
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
      return new Nodes::Node(Nodes::StatementRead, idx, ident);
    }
    case Tokens::LBrace: {
      accept(Tokens::LBrace);
      auto stmts = parseStatements();
      accept(Tokens::RBrace);
      return new Nodes::Node(Nodes::StatementBlock, stmts);
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
      err(6, Tokens::Ident, Tokens::KwWrite, Tokens::KwRead, Tokens::LBrace, Tokens::KwIf, Tokens::KwWhile);
      // can't be reached
      return nullptr;
  }
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
    case Tokens::Number: {
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
      err(5, Tokens::LParen, Tokens::Ident, Tokens::Number, Tokens::Minus, Tokens::Bang);
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
      break;

    default:
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
      delete token;
      nextToken();
      return new Nodes::Node(Nodes::Op, token);

    default:
      return new Nodes::Node(Nodes::Nil);
  }
}

unsigned Parser::parseInt()
{
  if (token->getTokenType() != Tokens::Number) {
    err(1, Tokens::Number);
  }

  auto i = token->getInt();
  accept(Tokens::Number);
  return i;
}

Symbol *Parser::parseIdent()
{
  if (token->getTokenType() != Tokens::Ident) {
    err(1, Tokens::Ident);
  }

  auto sym = token->symbol();
  accept(Tokens::Ident);
  return sym;
}

void Parser::accept(Tokens::TokenType tpe)
{
  if (token->getTokenType() != tpe) {
    err(1, tpe);
  }
  delete token;
  nextToken();
}

void Parser::err(unsigned count, ...)
{
  fprintf(stderr, "unexpected token '%s' at line '%d', column '%d'",
      token->getValue(), token->getLine(), token->getColumn());

  va_list argptr;
  va_start(argptr, count);
  if (count > 0) {
    auto t = (Tokens::TokenType) va_arg(argptr, int);
    fprintf(stderr, ". Expected: '%s'", Tokens::valueOf(t));
  }
  for (unsigned i = 1; i < count; ++i) {
    auto t = (Tokens::TokenType) va_arg(argptr, int);
    fprintf(stderr, " or '%s'", Tokens::valueOf(t));
  }
  va_end(argptr);

  fprintf(stderr, ".\n");
  exit(1);
}

void Parser::nextToken()
{
  token = scanner.nextToken();
}
