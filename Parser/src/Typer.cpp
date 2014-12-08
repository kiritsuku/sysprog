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
        auto s = node->arr()->symbol();

        if (s->type() == Type::IntArray)
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

    case StatementRead:
      break;

    case StatementIf:
      break;

    case StatementWhile:
      break;

    case StatementBlock:
      break;

    case Exp:
      break;

    case Exp2:
      break;

    case Exp2Ident:
      break;

    case Exp2Int:
      break;

    case Exp2Minus:
      break;

    case Exp2Neg:
      break;

    case Index:
      break;

    case OpExp:
      break;

    case Op:
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
