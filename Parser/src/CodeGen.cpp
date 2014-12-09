#include <string.h>
#include <math.h>
#include <stdio.h>
#include "CodeGen.h"

using namespace Nodes;

CodeGen::CodeGen():
  nrOfLabels(0),
  maxNrOfLabels(10),
  labels(new const char*[maxNrOfLabels])
{
}

CodeGen::~CodeGen()
{
  for (unsigned i = 0; i < nrOfLabels; ++i)
    delete[] labels[i];
  delete[] labels;
}

void CodeGen::makeCode(std::stringstream &ss, Node *node)
{
  switch(node->tpe()) {
    case Prog:
      makeCode(ss, node->decls());
      makeCode(ss, node->stmts());
      ss << "STP\n";
      break;

    case Decls:
      makeCode(ss, node->decl());
      makeCode(ss, node->nextDecl());
      break;

    case DeclArray:
      ss << "DS $" << node->symbol()->ident;
      makeCode(ss, node->arr());
      break;

    case DeclIdent:
      ss << "DS $" << node->symbol()->ident << " 1\n";
      break;

    case Array:
      ss << " " << node->intValue() << "\n";
      break;

    case Statements:
      makeCode(ss, node->stmt());
      makeCode(ss, node->nextStmt());
      break;

    case StatementIdent:
      makeCode(ss, node->exp());
      ss << "LA $" << node->symbol()->ident << "\n";
      makeCode(ss, node->index());
      ss << "STR\n";
      break;

    case StatementWrite:
      makeCode(ss, node->exp());
      ss << "PRI\n";
      break;

    case StatementRead:
      ss << "REA\n";
      ss << "LA $" << node->symbol()->ident;
      makeCode(ss, node->index());
      ss << "\nSTR\n";
      break;

    case StatementIf: {
      makeCode(ss, node->exp());
      auto l1 = mkLabel();
      ss << "JIN #" << l1 << "\n";
      makeCode(ss, node->ifStmt());
      auto l2 = mkLabel();
      ss << "JMP #" << l2 << "\n";
      ss << "#" << l1 << " NOP\n";
      makeCode(ss, node->elseStmt());
      ss << "#" << l2 << " NOP\n";
      break;
    }
    case StatementWhile: {
      auto l1 = mkLabel();
      ss << "#" << l1 << " NOP\n";
      makeCode(ss, node->exp());
      auto l2 = mkLabel();
      ss << "JIN #" << l2 << "\n";
      makeCode(ss, node->stmt());
      ss << "JMP #" << l1 << "\n";
      ss << "#" << l2 << " NOP\n";
      break;
    }

    case StatementBlock:
      makeCode(ss, node->stmts());
      break;

    case Exp: {
      auto ot = node->op()->type();
      if (ot == Type::NoType)
        makeCode(ss, node->exp2());
      else {
        auto oet = node->op()->op()->token()->getTokenType();
        if (oet == Tokens::Greater) {
          makeCode(ss, node->op());
          makeCode(ss, node->exp2());
          ss << "LES\n";
        }
        else if (oet == Tokens::SmallerColonGreater) {
          makeCode(ss, node->exp2());
          makeCode(ss, node->op());
          ss << "NOT\n";
        }
        else {
          makeCode(ss, node->exp2());
          makeCode(ss, node->op());
        }
      }
      break;
    }

    case Exp2:
      makeCode(ss, node->exp());
      break;

    case Exp2Ident:
      ss << "LA $" << node->symbol()->ident << "\n";
      makeCode(ss, node->index());
      ss << "LV\n";
      break;

    case Exp2Int:
      ss << "LC " << node->intValue() << "\n";
      break;

    case Exp2Minus:
      ss << "LC 0\n";
      makeCode(ss, node->exp2());
      ss << "SUB\n";
      break;

    case Exp2Neg:
      makeCode(ss, node->exp2());
      ss << "NOT\n";
      break;

    case Index:
      makeCode(ss, node->exp());
      ss << "ADD\n";
      break;

    case OpExp:
      makeCode(ss, node->exp());
      makeCode(ss, node->op());
      break;

    case Op:
      switch (node->token()->getTokenType()) {
        case Tokens::Plus:
          ss << "ADD\n";
          break;

        case Tokens::Minus:
          ss << "SUB\n";
          break;

        case Tokens::Mul:
          ss << "MUL\n";
          break;

        case Tokens::Div:
          ss << "DIV\n";
          break;

        case Tokens::Smaller:
          ss << "LES\n";
          break;

        case Tokens::Greater:
          // see rule for Exp
          break;

        case Tokens::Equals:
          ss << "EQU\n";
          break;

        case Tokens::SmallerColonGreater:
          ss << "EQU\n"; // see rule for Exp
          break;

        case Tokens::And:
          ss << "AND\n";
          break;

        default:
          break;
      }
      break;

    case Nil:
      break;
  }
}

void CodeGen::resize()
{
  auto old = labels;
  labels = new const char*[maxNrOfLabels*2];
  for (unsigned i = 0; i < nrOfLabels; ++i)
    labels[i] = old[i];
  maxNrOfLabels *= 2;
  delete[] old;
}

const char *CodeGen::mkLabel()
{
  if (nrOfLabels >= maxNrOfLabels)
    resize();

  auto nrOfDigits = nrOfLabels >= 1
    ? ((int) log10(nrOfLabels)+1)
    : 1;
  auto n = strlen("label")+nrOfDigits;
  auto buf = new char[n+1];

  sprintf(buf, "label%u", nrOfLabels);
  buf[n] = 0;
  labels[nrOfLabels] = buf;
  ++nrOfLabels;
  return buf;
}
