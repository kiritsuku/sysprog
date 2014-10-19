#include <stdio.h>
#include "Scanner.h"
#include "Automat.h"
#include "Buffer.h"

int main()
{
  auto fileName = "/home/antoras/xxx";
  Automat automat;
  Buffer buffer(fileName);
	Scanner scanner(automat, buffer);

  auto t = scanner.nextToken();
  printf("token: %s\n", Tokens::instance().text(t));
  return 0;
}

