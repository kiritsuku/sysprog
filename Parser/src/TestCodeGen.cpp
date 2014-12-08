#include "TestHelper.h"
#include "CodeGen.h"

void executeTest(Parser &parser)
{
  Typer typer;
  CodeGen codegen;

  auto node = parser.parse();
  typer.typeCheck(node);
  std::stringstream ss;
  codegen.makeCode(ss, node);
  printf("%s", ss.str().c_str());
  delete node;
}
