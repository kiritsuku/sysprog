#include <stdio.h>
#include <stdlib.h>
#include "Typer.h"

using namespace Nodes;

void Typer::typeCheck(Node *node)
{
  switch(node->tpe()) {
    case Prog:
      typeCheck(node->decls());
      typeCheck(node->stmts());
      node->setType(Type::NoType);
      break;

    case Decls:
      typeCheck(node->decl());
      typeCheck(node->nextDecl());
      break;

    case DeclArray:
      typeCheck(node->arr());

      if (node->symbol()->type() != Type::NoType)
        err("identifier already defined");
      else {
        if (node->symbol()->type() == Type::IntArray)
          node->symbol()->setType(Type::IntArray);
        else
          node->symbol()->setType(Type::Int);
      }
      break;

    case DeclIdent:
      if (node->symbol()->type() != Type::NoType)
        err("identifier already defined");
      else
        node->symbol()->setType(Type::Int);
      break;

    case Array:
      if (node->intValue() > 0)
        node->setType(Type::IntArray);
      else
        err("no valid dimension");
      break;

    case Statements:
      typeCheck(node->stmt());
      typeCheck(node->nextStmt());
      break;

    case StatementIdent: {
      typeCheck(node->exp());
      typeCheck(node->index());

      auto st = node->symbol()->type();
      if (st == Type::NoType)
        err("identifier not defined");
      else {
        auto et = node->exp()->type();
        auto it = node->index()->type();
        if (!(et == Type::Int && (
               (st == Type::Int && it == Type::NoType)
            || (st == Type::IntArray && it == Type::IntArray))))
          err("incompatible types");
      }
      break;
    }
    case StatementWrite:
      typeCheck(node->exp());
      break;

    case StatementRead: {
      typeCheck(node->index());

      auto st = node->symbol()->type();
      if (st == Type::NoType)
        err("identifier not defined");
      else {
        auto it = node->index()->type();
        if (!(
              (st == Type::Int && it == Type::NoType)
            ||(st == Type::IntArray && it == Type::IntArray)))
          err("incompatible types");
      }
      break;
    }

    case StatementIf:
      typeCheck(node->exp());
      typeCheck(node->ifStmt());
      typeCheck(node->elseStmt());
      break;

    case StatementWhile:
      typeCheck(node->exp());
      typeCheck(node->stmt());
      break;

    case StatementBlock:
      typeCheck(node->stmts());
      break;

    case Exp: {
      typeCheck(node->exp2());
      typeCheck(node->op());

      auto et = node->exp2()->type();
      auto ot = node->op()->type();

      if (ot == Type::NoType)
        node->setType(et);
      else if (et != ot)
        err("operator is not defined on expression");
      else
        node->setType(et);
      break;
    }
    case Exp2:
      typeCheck(node->exp());
      node->setType(node->exp()->type());
      break;

    case Exp2Ident: {
      typeCheck(node->index());

      auto st = node->symbol()->type();
      auto it = node->index()->type();

      if (st == Type::NoType)
        err("identifier not defined");
      else if (st == Type::Int && it == Type::NoType)
        node->setType(st);
      else if (st == Type::IntArray && it == Type::IntArray)
        node->setType(Type::Int);
      else
        err("no primitive type");
      break;
    }
    case Exp2Int:
      node->setType(Type::Int);
      break;

    case Exp2Minus:
      typeCheck(node->exp());
      node->setType(node->exp()->type());
      break;

    case Exp2Neg:
      typeCheck(node->exp());
      if (node->exp()->type() != Type::Int)
        err("can't negate non int type");
      else
        node->setType(Type::Int);
      break;

    case Index:
      typeCheck(node->exp());
      break;

    case OpExp:
      typeCheck(node->op());
      typeCheck(node->exp());
      node->setType(node->exp()->type());
      break;

    case Op:
      node->setType(Type::Int);
      break;

    case Nil:
      break;
  }
}

void Typer::err(const char *msg)
{
  fprintf(stderr, "Error while typechecking: %s\n", msg);
  exit(1);
}
