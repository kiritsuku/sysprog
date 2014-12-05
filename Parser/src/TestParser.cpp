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
  delete node;

  if (!noErr)
    handler.showErrorMessages();
  return handler.hasErrors() ? 1 : 0;
}
