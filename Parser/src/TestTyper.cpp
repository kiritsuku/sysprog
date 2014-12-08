#include "TestHelper.h"

void executeTest(Parser &parser)
{
  Typer typer;

  auto node = parser.parse();
  typer.typeCheck(node);
  printf("typechecking successful\n");
  delete node;
}
