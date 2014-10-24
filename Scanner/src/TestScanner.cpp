#include <stdio.h>
#include "Scanner.h"
#include "Automat.h"
#include "Buffer.h"
#include "Token.h"

int main()
{
  auto fileName = "";
  Automat automat;
  Buffer buffer(fileName);
	Scanner scanner(automat, buffer);

  auto t = scanner.nextToken();
  while (t != Tokens::Eof && t != Tokens::Error) {
    printf("token: %s\n", Tokens::instance().text(t));
    t = scanner.nextToken();
  }
  return 0;
}

