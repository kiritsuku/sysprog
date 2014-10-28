#include <stdio.h>
#include "Scanner.h"
#include "Automat.h"
#include "Buffer.h"
#include "Token.h"
#include "Symboltable.h"

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
	Scanner scanner(automat, buffer, symboltable);

  auto t = scanner.nextToken();
  while (t != Tokens::Eof) {
    printf("%s\n", t->text());
    if (t->isIdent() || t->isInt())
      delete t;
    t = scanner.nextToken();
  }
  return 0;
}

