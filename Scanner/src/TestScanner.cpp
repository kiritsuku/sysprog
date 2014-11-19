#include <stdio.h>
#include "Scanner.h"
#include "Automat.h"
#include "Buffer.h"
#include "Token.h"
#include "Symboltable.h"
#include "ErrorHandler.h"

int main(int argc, char* argv[])
{
  if (argc < 2) {
    fprintf(stderr, "Error: path to input file expected.\n");
    return -1;
  }

  auto fileName(argv[1]);
  Automat automat;
  Buffer buffer(fileName);
  Symboltable symboltable;
  ErrorHandler handler(fileName);
  Scanner scanner(automat, buffer, symboltable, handler);

  auto t = scanner.nextToken();
  while (t->getTokenType() != Tokens::Eof) {
    printf("Token %-22sLine: %d\tColumn: %d\t", t->typeText(), t->getLine(), t->getColumn());
    if (t->getTokenType() == Tokens::Ident)
      printf("Lexem: %s\n", t->getValue());
    else if (t->getTokenType() == Tokens::Number)
      printf("Value: %s\n", t->getValue());
    else
      printf("\n");
    delete t;
    t = scanner.nextToken();
  }
  delete t;

  handler.showErrorMessages();
  return handler.hasErrors() ? 1 : 0;
}

