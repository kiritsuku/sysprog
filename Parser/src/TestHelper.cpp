#include <sys/resource.h>
#include "TestHelper.h"

void mkNesting(std::stringstream &ss, unsigned nesting)
{
  for (unsigned i = 0; i < nesting; ++i)
    ss << "  ";
}

void mkString(std::stringstream &ss, Nodes::Node *node, unsigned nesting)
{
  switch (node->tpe()) {
    case Nodes::Prog:
      mkString(ss, node->decls(), nesting);
      mkString(ss, node->stmts(), nesting);
      break;

    case Nodes::Decls:
      mkString(ss, node->decl(), nesting);
      ss << ";\n";
      mkString(ss, node->nextDecl(), nesting);
      break;

    case Nodes::DeclArray:
      mkNesting(ss, nesting);
      ss << "int";
      mkString(ss, node->arr(), nesting);
      ss << " " << node->symbol()->ident;
      break;

    case Nodes::DeclIdent:
      mkNesting(ss, nesting);
      ss << "int " << node->symbol()->ident;
      break;

    case Nodes::Array:
      ss << "[" << node->intValue() << "]";
      break;

    case Nodes::Statements:
      mkString(ss, node->stmt(), nesting);
      ss << ";\n";
      mkString(ss, node->nextStmt(), nesting);
      break;

    case Nodes::StatementIdent:
      mkNesting(ss, nesting);
      ss << node->symbol()->ident;
      mkString(ss, node->index(), nesting);
      ss << " := ";
      mkString(ss, node->exp(), nesting);
      break;

    case Nodes::StatementWrite:
      mkNesting(ss, nesting);
      ss << "write(";
      mkString(ss, node->exp(), nesting);
      ss << ")";
      break;

    case Nodes::StatementRead:
      mkNesting(ss, nesting);
      ss << "read(" << node->symbol()->ident;
      mkString(ss, node->index(), nesting);
      ss << ")";
      break;

    case Nodes::StatementIf:
      mkNesting(ss, nesting);
      ss << "if(";
      mkString(ss, node->exp(), nesting);
      ss << ") ";
      mkString(ss, node->ifStmt(), nesting);
      mkNesting(ss, nesting);
      if (node->elseStmt()->tpe() != Nodes::Nil) {
        ss << " else ";
        mkString(ss, node->elseStmt(), nesting);
      }
      break;

    case Nodes::StatementWhile:
      mkNesting(ss, nesting);
      ss << "while(";
      mkString(ss, node->exp(), nesting);
      ss << ") ";
      mkString(ss, node->stmt(), nesting);
      break;

    case Nodes::StatementBlock:
      mkNesting(ss, nesting);
      ss << "{\n";
      mkString(ss, node->stmts(), nesting+1);
      mkNesting(ss, nesting);
      ss << "}";
      break;

    case Nodes::Exp:
      mkString(ss, node->exp2(), nesting);
      mkString(ss, node->op(), nesting);
      break;

    case Nodes::Exp2:
      ss << "(";
      mkString(ss, node->exp(), nesting);
      ss << ")";
      break;

    case Nodes::Exp2Ident:
      ss << node->symbol()->ident;
      mkString(ss, node->index(), nesting);
      break;

    case Nodes::Exp2Int:
      ss << node->intValue();
      break;

    case Nodes::Exp2Minus:
      ss << "-";
      mkString(ss, node->exp2(), nesting);
      break;

    case Nodes::Exp2Neg:
      ss << "!";
      mkString(ss, node->exp2(), nesting);
      break;

    case Nodes::Index:
      ss << "[";
      mkString(ss, node->exp(), nesting);
      ss << "]";
      break;

    case Nodes::OpExp:
      mkString(ss, node->op(), nesting);
      mkString(ss, node->exp(), nesting);
      break;

    case Nodes::Op:
      ss << node->token()->getValue();
      break;

    case Nodes::Nil:
      break;
  }
}

static int increaseStackSize()
{
  // stack size in MB
  const rlim_t stackSize = 1024*1024*50;
  struct rlimit rl;
  auto res = getrlimit(RLIMIT_STACK, &rl);
  if (res == 0 && rl.rlim_cur < stackSize) {
    rl.rlim_cur = stackSize;
    res = setrlimit(RLIMIT_STACK, &rl);
    if (res != 0) {
      fprintf(stderr, "Error: couldn't increase stacksize. setrlimet returned '%d'\n.", res);
    }
  }
  return res;

}

int main(int argc, char* argv[])
{
  if (argc < 2) {
    fprintf(stderr, "Error: path to input file expected.\n");
    return -1;
  }

  increaseStackSize();

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

  executeTest(parser);

  if (!noErr)
    handler.showErrorMessages();
  return handler.hasErrors() ? 1 : 0;
}
