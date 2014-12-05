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
      break;

    case Nodes::StatementIdent:
      break;

    case Nodes::StatementWrite:
      break;

    case Nodes::StatementRead:
      break;

    case Nodes::StatementBlock:
      break;

    case Nodes::StatementIf:
      break;

    case Nodes::StatementWhile:
      break;

    case Nodes::Exp:
      break;

    case Nodes::Exp2:
      break;

    case Nodes::Exp2Ident:
      break;

    case Nodes::Exp2Int:
      break;

    case Nodes::Exp2Minus:
      break;

    case Nodes::Exp2Neg:
      break;

    case Nodes::Index:
      break;

    case Nodes::OpExp:
      break;

    case Nodes::Op:
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
