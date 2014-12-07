#include <stdio.h>
#include <string.h>
#include "Scanner.h"
#include "Automat.h"
#include "Buffer.h"
#include "Token.h"
#include "Symboltable.h"
#include "ErrorHandler.h"
#include "Parser.h"
#include "Nodes.h"

#include <sstream>

void mkString(std::stringstream &ss, Nodes::Node *node)
{
  switch (node->tpe()) {
    case Nodes::Prog:
      mkString(ss, node->decls());
      mkString(ss, node->stmts());
      break;

    case Nodes::Decls:
      mkString(ss, node->decl());
      ss << ";\n";
      mkString(ss, node->nextDecl());
      break;

    case Nodes::DeclArray:
      ss << "int";
      mkString(ss, node->arr());
      ss << " " << node->symbol()->ident;
      break;

    case Nodes::DeclIdent:
      ss << "int " << node->symbol()->ident;
      break;

    case Nodes::Array:
      ss << "[" << node->intValue() << "]";
      break;

    case Nodes::Statements:
      mkString(ss, node->stmt());
      ss << "\n";
      mkString(ss, node->nextStmt());
      break;

    case Nodes::StatementIdent:
      ss << node->symbol()->ident;
      mkString(ss, node->index());
      ss << " := ";
      mkString(ss, node->exp());
      break;

    case Nodes::StatementWrite:
      ss << "write(";
      mkString(ss, node->exp());
      ss << ")";
      break;

    case Nodes::StatementRead:
      ss << "read(" << node->symbol()->ident;
      mkString(ss, node->index());
      ss << ")";
      break;

    case Nodes::StatementIf:
      ss << "if(";
      mkString(ss, node->exp());
      ss << ") ";
      mkString(ss, node->ifStmt());
      ss << "else ";
      mkString(ss, node->elseStmt());
      break;

    case Nodes::StatementWhile:
      ss << "while(";
      mkString(ss, node->exp());
      ss << ") ";
      mkString(ss, node->stmt());
      break;

    case Nodes::StatementBlock:
      ss << "{\n";
      mkString(ss, node->stmts());
      ss << "\n}\n";

    case Nodes::Exp:
      mkString(ss, node->exp2());
      mkString(ss, node->op());
      break;

    case Nodes::Exp2:
      ss << "(";
      mkString(ss, node->exp());
      ss << ")";
      break;

    case Nodes::Exp2Ident:
      ss << node->symbol()->ident;
      mkString(ss, node->index());
      break;

    case Nodes::Exp2Int:
      ss << node->intValue();
      break;

    case Nodes::Exp2Minus:
      ss << "-";
      mkString(ss, node->exp2());
      break;

    case Nodes::Exp2Neg:
      ss << "!";
      mkString(ss, node->exp2());
      break;

    case Nodes::Index:
      ss << "[";
      mkString(ss, node->exp());
      ss << "]";
      break;

    case Nodes::OpExp:
      mkString(ss, node->op());
      mkString(ss, node->exp());
      break;

    case Nodes::Op:
      ss << node->token()->getValue();
      break;

    case Nodes::Nil:
      break;
  }
}

int main(int argc, char* argv[])
{
  if (argc < 2) {
    fprintf(stderr, "Error: path to input file expected.\n");
    return -1;
  }

  auto fileName(argv[1]);
  auto noErr = false;
  for (auto i = 2; i < argc; ++i) {
    if (strcmp(argv[i], "--noerr") == 0)
      noErr = true;
    else if (strcmp(argv[i], "") != 0) {
      fprintf(stderr, "Error: Unknown flag '%s'.\n", argv[i]);
      return -1;
    }
  }

  Automat automat;
  Buffer buffer(fileName);
  Symboltable symboltable;
  ErrorHandler handler(fileName);
  Scanner scanner(automat, buffer, symboltable, handler);
  Parser parser(scanner, handler);

  auto node = parser.parse();
  std::stringstream ss;
  mkString(ss, node);
  printf("%s\n", ss.str().c_str());
  delete node;

  if (!noErr)
    handler.showErrorMessages();
  return handler.hasErrors() ? 1 : 0;
}
