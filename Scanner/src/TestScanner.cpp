#include <stdio.h>
#include "Scanner.h"
#include "Automat.h"
#include "Buffer.h"
#include "Token.h"
#include "Symboltable.h"

int main()
{
  auto fileName = "";
  Automat automat;
  Buffer buffer(fileName);
  Symboltable symboltable;
	Scanner scanner(automat, buffer, symboltable);

  auto t = scanner.nextToken();
  while (t != Tokens::Eof && t != Tokens::Error) {
    printf("token: %s\n", t->text());
    if (t->isIdent())
      delete t;
    t = scanner.nextToken();
  }
  return 0;
}

